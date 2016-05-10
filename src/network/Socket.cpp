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

void gauntlet::network::Socket::send(void *data, size_t size) {
    writeLock.lock();
    if (type == SERVER) {
        for (s_client cli : clients) {
            write(cli.sockfd, data, size);
        }
    } else {
        write(sockfd, data, size);
    }
    writeLock.unlock();
}

void *gauntlet::network::Socket::recv() {
    fd_set *set;
    s_client cli;
    size_t nfds;

    if (type == SERVER) {
        while (1) {
            nfds = clients.size() + 1;
            set = new fd_set[nfds];

            for (size_t i = 0; i < nfds; i++) {
                FD_ZERO(set + i);
                FD_SET((i == 0 ? sockfd : clients[i - 1].sockfd), set + i);
            }
            select((clients.size() == 0 ? sockfd : clients[clients.size() - 1].sockfd) + 1, set, NULL, NULL, NULL);

            for (size_t i = 0; i < nfds; i++) {
                if (!i) {
                    cli.len = sizeof(cli.sock);
                    cli.sockfd = accept(sockfd, (struct sockaddr *) &cli.sock, &cli.len);
                    clients.push_back(cli);
                } else {
                    if (FD_ISSET(clients[i - 1].sockfd, set + i)) {
                        void *ret = this->recv(clients[i - 1].sockfd);
                        delete set;
                        return ret;
                    }
                }
            }
            delete set;
        }
    }
    return this->recv(sockfd);
}

void *gauntlet::network::Socket::recv(int fd) {
    ssize_t size;
    char buff[BUFFER_SIZE];
    void *ret = NULL;
    size_t retsize = 0;

    readLock.lock();
    while ((size = ::recv(fd, buff, BUFFER_SIZE, MSG_DONTWAIT)) > 0) {
        ret = realloc(ret, retsize + size);
        memcpy(((char *)ret) + retsize, buff, size);
        retsize += size;
    }
    readLock.unlock();
    return ret;
}


gauntlet::network::SocketType gauntlet::network::Socket::getType() const {
    return type;
}