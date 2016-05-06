//
// Created by guemasg on 13/04/16.
//

#include <netdb.h>
#include <stdexcept>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <SocketException.hpp>
#include <cstdlib>
#include "NSocket.hpp"

NSocket::NSocket()
{
  this->sin = new sockaddr_in;
  bzero(this->sin, sizeof(sockaddr_in));
}

NSocket::~NSocket()
{
  close(this->fd_buff);
}

void NSocket::init()
{
  if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      throw (SocketException("socket fail", strerror(errno)));
    }
}

void NSocket::connect(std::string const &addr)
{
  struct hostent *hostinfo = NULL;

  std::string host = addr.substr(0, addr.find(':'));
  std::string port = addr.substr(addr.find(':') + 1);

  hostinfo = gethostbyname(host.c_str());
  if (hostinfo == NULL) /* l'hôte n'existe pas */
    {
      throw (SocketException("Host not found :" + addr, ""));
    }
  sin->sin_addr = *(in_addr *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
  sin->sin_port = htons(std::stoi(port)); /* on utilise htons pour le port */
  sin->sin_family = AF_INET;
  if (::connect(this->sock_fd, (sockaddr *) sin, sizeof(sockaddr)) == -1)
    {
      throw (SocketException("connect fail", strerror(errno)));
    }
}

void NSocket::listen()
{
  if (::listen(this->sock_fd, 512) < 0)
    {
      throw (SocketException("listenEvents fail", strerror(errno)));
    }
}

void NSocket::bind(std::string const &addr)
{
  std::string port = addr.substr(addr.find(':') + 1);

  sin->sin_addr.s_addr = htonl(
	  INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
  sin->sin_family = AF_INET;
  sin->sin_port = htons(std::stoi(port));

  if (::bind(this->sock_fd, (sockaddr *) sin, sizeof(sockaddr)) == -1)
    {
      throw (SocketException("bind fail", strerror(errno)));
    }
}

void NSocket::accept()
{
  socklen_t fromlen = sizeof(struct sockaddr);
  struct sockaddr_in fsaun;
  if ((this->fd_buff = ::accept(this->sock_fd, (struct sockaddr *) &fsaun,
				(&fromlen))) < 0)
    {
      throw (SocketException("accept fail", strerror(errno)));
    }
}

void NSocket::send(void *data, int len, int fd)
{
  if (!::send(fd, data, len, MSG_DONTWAIT) == -1)
    throw std::runtime_error(std::string("NSocket send: ") + strerror(errno));
}

void NSocket::send(void *data, int len)
{
  if (this->fd_buff != -1)
    {
      this->send(data, len, this->fd_buff);
      return;
    }
  this->send(data, len, this->sock_fd);
}

void *NSocket::recv(size_t size)
{
  if (this->fd_buff == -1)
    {
      return this->recv(size, this->sock_fd);
    }
  return this->recv(size, this->fd_buff);
}

void *NSocket::recv(size_t size, int fd)
{
  return this->recv(size, fd, true);
}

void *NSocket::recv(size_t size, int fd, bool timeout)
{
  ssize_t l;
  void *data;

  data = malloc(size);
  if ((l = ::recv(fd, data, size, (timeout ? 0 : MSG_DONTWAIT))) == -1)
    {
      free(data);
      throw (SocketException("recv fail on fd " + fd, strerror(errno)));
    }
  return data;
}


int NSocket::getFd()
{
  return this->sock_fd;
}

int NSocket::getAcceptedFd()
{
  if (this->fd_buff == -1)
    {
      throw SocketException("", "No accepted connexion");
    }
  return this->fd_buff;
}
