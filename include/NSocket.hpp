//
// Created by guemasg on 13/04/16.
//



#ifndef CPP_PLAZZA_NSOCKET_HPP
#define CPP_PLAZZA_NSOCKET_HPP

#include <string>

static const char *const ipAddressPortRegex = "([0-9])+\\.([0-9])+\\.([0-9])+\\.([0-9])+\\:[0-9]+";

class NSocket
{
 private:
  struct sockaddr_in *sin;
  int sock_fd;
  int fd_buff;

 public:
  NSocket();

  ~NSocket();

  void init();

  void connect(std::string const &addr);

  void listen();

  void bind(std::string const &addr);

  void accept();

  void send(void *data, int len);

  void send(void *data, int len, int fd);

  void *recv(size_t size);

  void *recv(size_t size, int fd);

  int getFd();

  int getAcceptedFd();

  void *recv(size_t size, int fd, bool timeout);
};


#endif //CPP_PLAZZA_NSOCKET_HPP
