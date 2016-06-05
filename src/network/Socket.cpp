//
// Created by drouar_b on 5/9/16.
//

#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "network/Socket.hh"

gauntlet::network::Socket::Socket(in_port_t port) {
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
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
    type = SERVER;
    disconnectionListener = NULL;
}

gauntlet::network::Socket::Socket(const std::string &address, in_port_t port) {
    ::pipe(pipe);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::runtime_error("Can't open socket");
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(address.c_str());
    if (connect(sockfd, (struct sockaddr *) &sock, sizeof(sock)) == -1)
        throw std::runtime_error("Connection error");
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
            ::send(cli.sockfd, &data->front(), data->size(), 0);
        }
    } else {
        ::send(sockfd, &data->front(), data->size(), 0);
    }
    lock.unlock();
}

void gauntlet::network::Socket::send(std::vector<unsigned char> *data, int fd) {
    lock.lock();
    if (type == SERVER) {
        for (s_client client : clients) {
            if (client.sockfd == fd)
                ::send(client.sockfd, &data->front(), data->size(), 0);
        }
    } else {
        if (fd == sockfd)
            ::send(sockfd, &data->front(), data->size(), 0);
    }
    lock.unlock();
}

s_socketData gauntlet::network::Socket::recv() {
    fd_set set;
    s_client cli;
    s_socketData buff;

    if (type == SERVER) {
        cli.len = sizeof(cli.sock);
        while (1) {
            bzero(&set, sizeof(fd_set));
            FD_ZERO(&set);

            FD_SET(pipe[0], &set);
            FD_SET(sockfd, &set);
            for (s_client client : clients) {
                FD_SET(client.sockfd, &set);
            }

            select(FD_SETSIZE, &set, NULL, NULL, NULL);

            lock.lock();
            for (int i = 0; i < FD_SETSIZE; i++) {
                if (FD_ISSET(i, &set)) {
                    if (i == pipe[0]) {
                        buff = this->recv(pipe[0]);
                        buff.data->resize(0);
                        buff.fd = -1;
                        return buff;
                    }
                    if (i == sockfd) {
                        while ((cli.sockfd = accept(sockfd, (struct sockaddr *) &cli.sock, &cli.len)) != -1) {
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
    FD_SET(pipe[0], &set);
    FD_SET(sockfd, &set);
    select((pipe[0] > sockfd ? pipe[0] : sockfd) + 1, &set, NULL, NULL, NULL);
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
    ssize_t readSize;
    s_socketData data;
    static std::vector<unsigned char> buffer(BUFFER_SIZE, 0);
    data.data = new std::vector<unsigned char>();

    while ((readSize = ::recv(fd, &buffer.front(), BUFFER_SIZE, MSG_DONTWAIT)) > 0) { //TODO: segfault here
        data.data->insert(data.data->end(), buffer.begin(), buffer.begin() + readSize);
    }
    if (!readSize)
        this->notifyDisconnection(fd);
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
