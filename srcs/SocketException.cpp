//
// Created by celeri_y on 4/13/16.
//

#include "SocketException.hpp"

const char *SocketException::what() const throw()
{
  std::stringstream stringstream;

  stringstream << "Socket Error: " << this->reason << ". " << this->description;
  return (stringstream.str().c_str());
}

SocketException::SocketException(std::string const &description,
					 std::string const &reason)
	: description(
	description), reason(reason)
{

}