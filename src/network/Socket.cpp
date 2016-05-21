//
// Created by drouar_b on 5/9/16.
//

#include <stdexcept>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "network/Socket.hh"

gauntlet::network::Socket::Socket(in_port_t port) {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::logic_error("Can't open socket");
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = INADDR_ANY;
    sock.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &sock, sizeof(sock)) == -1)
        throw std::logic_error("Can't bind port");
    if (listen(sockfd, 0) == -1)
        throw std::logic_error("Listen error");
    type = SERVER;
}

gauntlet::network::Socket::Socket(const std::string &address, in_port_t port) {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::logic_error("Can't open socket");
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(address.c_str());
    if (connect(sockfd, (struct sockaddr *) &sock, sizeof(sock)) == -1)
        throw std::logic_error("Connection error");
    type = CLIENT;
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

std::vector<unsigned char> *gauntlet::network::Socket::recv() {
    int maxfd;
    fd_set set;
    s_client cli;

    if (type == SERVER) {
        cli.len = sizeof(cli.sock);
        while (1) {
            bzero(&set, sizeof(fd_set));
            FD_ZERO(&set);
            maxfd = (clients.size() == 0 ? sockfd : clients.back().sockfd) + 1;

            FD_SET(sockfd, &set);
            for (s_client cli : clients) {
                FD_SET(cli.sockfd, &set);
            }

            select(maxfd, &set, NULL, NULL, NULL);

            lock.lock();
            for (size_t i = 3; i < maxfd; i++) {
                if (FD_ISSET(i, &set)) {
                    if (i == sockfd) {
                        if ((cli.sockfd = accept(sockfd, (struct sockaddr *) &cli.sock, &cli.len)) != -1) {
                            clients.push_back(cli);
                        }
                    } else {
                        return this->recv(i, 1);
                    }
                    FD_CLR(i, &set);
                }
            }
            lock.unlock();
        }
    }
    lock.lock();
    return this->recv(sockfd, 0);
}

std::vector<unsigned char> *gauntlet::network::Socket::recv(int fd, int loop) {
    ssize_t readSize;
    static std::vector<unsigned char> buffer(BUFFER_SIZE, 0);
    std::vector<unsigned char> *data = new std::vector<unsigned char>();

    while ((readSize = ::recv(fd, &buffer.front(), BUFFER_SIZE, (loop++ != 0 ? MSG_DONTWAIT : 0))) > 0) {
        data->insert(data->end(), buffer.begin(), buffer.begin() + readSize);
    }
    lock.unlock();
    return data;
}


gauntlet::network::SocketType gauntlet::network::Socket::getType() const {
    return type;
}