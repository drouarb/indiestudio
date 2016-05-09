//
// Created by drouar_b on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SOCKET_HH
#define CPP_INDIE_STUDIO_SOCKET_HH

#include <cstdlib>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <mutex>

#define BUFFER_SIZE     4096

namespace gauntlet {
    namespace network {
        enum SocketType {
            CLIENT,
            SERVER
        };

        struct s_client {
            int         sockfd;
            sockaddr_in sock;
            socklen_t   len;
        };

        class Socket {
        public:
            Socket(in_port_t port);
            Socket(const std::string &address, in_port_t port);
            ~Socket();
            void send(void *data, size_t size);
            void *recv();
            SocketType getType() const;

        private:
            void *recv(int fd);

        private:
            SocketType type;
            struct sockaddr_in sock;
            int sockfd;
            std::vector<s_client> clients;
            std::mutex writeLock;
            std::mutex readLock;
        };
    }
}


#endif //CPP_INDIE_STUDIO_SOCKET_HH
