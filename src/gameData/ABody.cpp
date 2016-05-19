//
// ABody.cpp for ABody in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:07:25 2016 Alexis Trouve
// Last update Thu May 19 16:19:40 2016 Alexis Trouve
//

#include <iostream>
#include "ABody.hh"

using namespace gauntlet;

ABody::ABody(int nid)
{
  id = nid;
  collideActive = true;
  coord.first = 0;
  coord.second = 0;
  size.first = 0;
  size.second = 0;
  orientation = 0;
  name = "default";
}

ABody::~ABody()
{

}

void				ABody::changePos(const std::pair<double, double>& ncoord)
{
  coord = ncoord;
}

void				ABody::changeSize(const std::pair<double, double>& nsize)
{
  size = nsize;
}

void				ABody::changeOrientation(short norient)
{
  orientation = norient;
}

std::pair<double, double> const &	ABody::getPos() const
{
  return (coord);
}

std::pair<double, double> const &	ABody::getSize() const
{
  return (size);
}

short				ABody::getOrientation() const
{
  return (orientation);
}

int				ABody::getId() const
{
  return (id);
}

bool				ABody::getCollide() const
{
  return (collideActive);
}

void				ABody::setCollide(bool ncollide)
{
  collideActive = ncollide;
}

const std::string&		ABody::getName() const
{
  return (name);
}

void				ABody::setName(const std::string& nname)
{
  name = nname;
}
