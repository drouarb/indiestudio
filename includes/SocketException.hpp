//
// Created by celeri_y on 4/13/16.
//

#ifndef CPP_PLAZZA_SOCKETEXCEPTION_HPP
#define CPP_PLAZZA_SOCKETEXCEPTION_HPP

#include <string>
#include <exception>
#include <iostream>
#include <sstream>

class SocketException : public std::exception
{
 private:
  std::string const description;
  std::string const reason;

 public:
  SocketException(std::string const &description, std::string const &reason);

  const char *what() const throw();
};

#endif //CPP_PLAZZA_SOCKETEXCEPTION_HPP
