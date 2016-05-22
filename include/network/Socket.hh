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
#include "ISocketDisconnectionListener.hh"

#define BUFFER_SIZE     4096

struct s_socketData {
    int fd;
    std::vector<unsigned char>* data;
};

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
            void unlock();
            void send(std::vector<unsigned char>* data);
            s_socketData recv();
            SocketType getType() const;
            void setDisconnectionListener(ISocketDisconnectionListener *listener);

        private:
            void notifyDisconnection(int fd);
            s_socketData recv(int fd);

        private:
            int pipe[2];
            SocketType type;
            struct sockaddr_in sock;
            int sockfd;
            std::vector<s_client> clients;
            std::mutex lock;
            ISocketDisconnectionListener *disconnectionListener;
        };
    }
}


#endif //CPP_INDIE_STUDIO_SOCKET_HH
