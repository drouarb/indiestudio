//
// Created by drouar_b on 5/9/16.
//

#include <stdexcept>
#include <string.h>
#include <fcntl.h>
#include "network/Socket.hh"

gauntlet::network::Socket::Socket(unsigned short port) {
#ifdef _WIN32
	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    ::pipe(pipe);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::runtime_error("Can't open socket");
	sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = INADDR_ANY;
    sock.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &sock, sizeof(sock)) == -1)
        throw std::runtime_error("Can't bind port");
	if (listen(sockfd, 0) == -1)
        throw std::runtime_error("Listen error");

#ifdef _WIN32
	unsigned long mode = 1;
	ioctlsocket(sockfd, FIONBIO, &mode);
#else
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
#endif
    type = SERVER;
    disconnectionListener = NULL;
}

gauntlet::network::Socket::Socket(const std::string &address, unsigned short port) {
#ifdef _WIN32
	WSADATA wsaData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
	
	::pipe(pipe);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::runtime_error("Can't open socket");
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(address.c_str());
    if (connect(sockfd, (struct sockaddr *) &sock, sizeof(sock)) == -1)
        throw std::runtime_error("Connection error");
#ifdef _WIN32
	unsigned long mode = 1;
	ioctlsocket(sockfd, FIONBIO, &mode);
#endif
	type = CLIENT;
	disconnectionListener = NULL;
}

gauntlet::network::Socket::~Socket() {
    for (s_client cli : clients) {
        close(cli.sockfd);
    }
    close(sockfd);
}

void gauntlet::network::Socket::send(std::vector<unsigned char> *data) {
    lock.lock();
    if (type == SERVER) {
      for (s_client cli : clients) {
            ::send(cli.sockfd, (char *)&data->front(), data->size(), 0);
        }
    } else {
        ::send(sockfd, (char *)&data->front(), data->size(), 0);
    }
    lock.unlock();
}

void gauntlet::network::Socket::send(std::vector<unsigned char> *data, int fd) {
    lock.lock();
    if (type == SERVER) {
        for (s_client client : clients) {
            if (client.sockfd == fd)
                ::send(client.sockfd, (char *)&data->front(), data->size(), 0);
        }
    } else {
        if (fd == sockfd)
            ::send(sockfd, (char *)&data->front(), data->size(), 0);
    }
    lock.unlock();
}

s_socketData gauntlet::network::Socket::recv() {
	SOCKET max;
    fd_set set;
    s_client cli;
    s_socketData buff;
	unsigned long mode = 1;

    if (type == SERVER) {
        cli.len = sizeof(cli.sock);
        while (1) {
			memset(&set, 0, sizeof(fd_set));
            FD_ZERO(&set);

            FD_SET(sockfd, &set);
			max = sockfd;
#ifndef _WIN32
			FD_SET(pipe[0], &set);
			max = (pipe[0] > max ? pipe[0] : max);
#endif
			for (s_client client : clients) {
                FD_SET(client.sockfd, &set);
				max = (client.sockfd > max ? client.sockfd : max);
			}

			select(max + 1, &set, NULL, NULL, NULL);

            lock.lock();
            for (int i = 0; i < max + 1; i++) {
                if (FD_ISSET(i, &set)) {
					if (i == pipe[0]) {
                        buff = this->recv(pipe[0]);
                        buff.data->resize(0);
                        buff.fd = -1;
                        return buff;
                    }
                    if (i == sockfd) {
                        while ((cli.sockfd = accept(sockfd, (struct sockaddr *) &cli.sock, &cli.len)) != -1) {
#ifdef _WIN32
							ioctlsocket(cli.sockfd, FIONBIO, &mode);
#endif
                            clients.push_back(cli);
                        }
                    } else {
                        buff = this->recv(i);
                        if (buff.data->size() == 0) {
                            delete buff.data;
                        } else {
                            return buff;
                        }
                    }
                    FD_CLR(i, &set);
                }
            }
            lock.unlock();
        }
    }
    FD_ZERO(&set);
	FD_SET(sockfd, &set);
#ifdef _WIN32
	select(sockfd + 1, &set, NULL, NULL, NULL);
#else
	FD_SET(pipe[0], &set);
	select((pipe[0] > sockfd ? pipe[0] : sockfd) + 1, &set, NULL, NULL, NULL);
#endif
	lock.lock();
    if (FD_ISSET(pipe[0], &set)) {
        buff = this->recv(pipe[0]);
        buff.data->resize(0);
        buff.fd = -1;
        return buff;
    }
    return this->recv(sockfd);
}

s_socketData gauntlet::network::Socket::recv(int fd) {
    int readSize;
    s_socketData data;
    static std::vector<unsigned char> buffer(BUFFER_SIZE, 0);
    data.data = new std::vector<unsigned char>();

    while ((readSize = ::recv(fd, (char *)&buffer.front(), BUFFER_SIZE, MSG_DONTWAIT)) > 0) {
        data.data->insert(data.data->end(), buffer.begin(), buffer.begin() + readSize);
    }
#ifdef _WIN32
	int nError = WSAGetLastError();
	if (nError != WSAEWOULDBLOCK && nError != 0)
		this->notifyDisconnection(fd);
#else
    if (!readSize)
        this->notifyDisconnection(fd);
#endif
    data.fd = fd;
    lock.unlock();
    return data;
}

void gauntlet::network::Socket::unlock() {
    write(pipe[1], "\0", 1);
}

gauntlet::network::SocketType gauntlet::network::Socket::getType() const {
    return type;
}

void gauntlet::network::Socket::notifyDisconnection(int fd) {
    if (type == SERVER) {
        for (std::vector<s_client>::iterator it = clients.begin(); it < clients.end(); it++) {
            if ((*it).sockfd == fd) {
                close(fd);
                clients.erase(it);
                break;
            }
        }
    }
    if (disconnectionListener)
        disconnectionListener->notify(fd);
}

void gauntlet::network::Socket::setDisconnectionListener(ISocketDisconnectionListener *listener) {
    disconnectionListener = listener;
}
