//
// Created by drouar_b on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SOCKET_HH
#define CPP_INDIE_STUDIO_SOCKET_HH

#ifdef _WIN32
#include <io.h>
#include <winsock.h>
#define pipe(x) _pipe(x, 1024, O_BINARY);
#define MSG_DONTWAIT 0
#define in_port_t unsigned short
#define socklen_t int
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define SOCKET int
#endif

#include <cstdlib>
#include <string>
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
            Socket(unsigned short port);
            Socket(const std::string &address, unsigned short port);
            ~Socket();
            void unlock();
            void send(std::vector<unsigned char>* data);
            void send(std::vector<unsigned char>* data, int fd);
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
			SOCKET sockfd;
            std::vector<s_client> clients;
            std::mutex lock;
            ISocketDisconnectionListener *disconnectionListener;
        };
    }
}


#endif //CPP_INDIE_STUDIO_SOCKET_HH
