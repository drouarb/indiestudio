//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Fri May 20 13:43:41 2016 Alexis Trouve
//

#include <iostream>
#include "world/PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(unsigned int sizex, unsigned int sizey)
{
  sizeX = sizex;
  sizeY = sizey;
  layer = new unsigned char[sizeX * sizeY];
}

PhysicCollideLayer::~PhysicCollideLayer()
{}

std::pair<double, double>    PhysicCollideLayer::getSize() const
{
  return (std::make_pair(sizeX, sizeY));
}

void PhysicCollideLayer::setWall(unsigned int x, unsigned int y) 
{
  if (x > sizeX || y > sizeY)
    return ;
  layer[(y * sizeX) + x] = 1;
}

void    PhysicCollideLayer::setWall(double xpos, double ypos, double xsize, double ysize)
{
  unsigned int	y;
  unsigned int	x;
  unsigned int	maxX;
  unsigned int	maxY;

  y = static_cast<unsigned int>(ypos);
  maxX = static_cast<unsigned int>(xpos + xsize);
  maxY = static_cast<unsigned int>(ypos + ysize);
  if (maxX >= sizeX || maxY >= sizeY)
    return ;
  while (y < maxY)
    {
      x = static_cast<unsigned int>(xpos);
      while (x < maxX)
	if (x % 8 == 0 && maxX - x > 8)
	  {
	    layer[(y * sizeX) + x] = 255;
	    x += 8;
	  }
	else
	  setWall(x++, y);
      ++y;
    }
}

void PhysicCollideLayer::unsetWall(unsigned int x, unsigned int y)
{
  if (x > sizeX || y > sizeY)
    return ;
  layer[(y * sizeX) + x] = 0;
}

bool PhysicCollideLayer::isWall(unsigned int x, unsigned int y)
{
  if (layer[(y * sizeX) + x] == 0)
    return (false);
  return (true);
}

void    PhysicCollideLayer::unsetWall(double xpos, double ypos, double xsize, double ysize)
{
  unsigned int	y;
  unsigned int	x;
  unsigned int	maxX;
  unsigned int	maxY;

  y = static_cast<unsigned int>(ypos);
  maxX = static_cast<unsigned int>(xpos + xsize);
  maxY = static_cast<unsigned int>(ypos + ysize);
  if (maxX >= sizeX || maxY >= sizeY)
    return ;
  while (y < maxY)
    {
      x = static_cast<unsigned int>(xpos);
      while (x < maxX)
	if (x % 8 == 0 && maxX - x > 8)
	  {
	    layer[(y * sizeX) + x] = 0;
	    x += 8;
	  }
	else
	  setWall(x++, y);
      ++y;
    }
}

bool    PhysicCollideLayer::checkCoordSize(double xpos, double ypos, double xsize, double ysize)
{
  unsigned int	minX;
  unsigned int	minY;
  unsigned int	maxX;
  unsigned int	maxY;
  unsigned int	y;
  unsigned int	x;

  minX = static_cast<unsigned int>(((xpos - xsize) - static_cast<unsigned int>(xpos - xsize) < 0.0)
			      ? xpos - xsize - 1 : xpos - xsize);
  minY = static_cast<unsigned int>(((ypos - ysize) - static_cast<unsigned int>(ypos - ysize) < 0.0)
			      ? ypos - ysize - 1 : ypos - ysize);
  maxX = static_cast<unsigned int>(((xpos - xsize) - static_cast<unsigned int>(xpos - xsize) > 0.0)
			      ? xpos - xsize - 1 : xpos - xsize);
  maxX = static_cast<unsigned int>(((ypos - ysize) - static_cast<unsigned int>(ypos - ysize) > 0.0)
			      ? ypos - ysize - 1 : ypos - ysize);
  y = minY;
  if (maxX >= sizeX || maxY >= sizeY || minX >= sizeX || minY >= sizeX)
    return (false);
  while (y < maxY)
    {
      x = minX;
      while (x < maxX)
	{
	  if (x % 8 == 0 && maxX - x > 8)
	    {
	      if (layer[(y * sizeX) + x] > 0)
		return (false);
	      x += 8;
	    }
	  else
	    isWall(x++, y);
	}
      ++y;
    }
}

const unsigned char *PhysicCollideLayer::getLayer() const
{
  return (layer);
}
