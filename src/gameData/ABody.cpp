//
// ABody.cpp for ABody in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:07:25 2016 Alexis Trouve
// Last update Wed May 18 14:13:59 2016 Esteban Lewis
//

#include "ABody.hh"

using namespace gauntlet;

ABody::ABody(bool collide, int nid, double posx,
				 double posy, double sizex, double sizey, short norient)
{
  collideActive = collide;
  id = nid;
  coord = std::make_pair(posx, posy);
  size = std::make_pair(sizex, sizey);
  orientation = norient;
}

ABody::ABody(int nid, double posx, double posy,
				 double sizex, double sizey, short norient)
{
  collideActive = true;
  id = nid;
  coord = std::make_pair(posx, posy);
  size = std::make_pair(sizex, sizey);
  orientation = norient;
}

ABody::~ABody()
{

}

bool				ABody::isCollide(std::pair<double, double> chackpos,
						      std::pair<double, double> checkSize)
{
  return (false);
}

void				ABody::changePos(double nposx, double nposy)
{
  coord = std::make_pair(nposx, nposy);
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
