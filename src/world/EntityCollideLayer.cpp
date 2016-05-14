//
// EntityCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 11:03:19 2016 Alexis Trouve
// Last update Sat May 14 12:05:33 2016 Alexis Trouve
//

#include <err.h>
#include "EntityCollideLayer.hh"

using namespace gauntlet;
using namespace world;

EntityCollideLayer::EntityCollideLayer(gauntlet::world::PhysicCollideLayer *physicLayer)
{
  int				i;
  std::pair<double, double>	size;

  size = physicLayer->getSize();
  i = 0;
  if ((map = new CollidingArea*[static_cast<int>(size.first / SIZE_CASE)]) == NULL)
    errx(1, "Error : out of memory");
  sizeX = static_cast<int>(size.first / SIZE_CASE);
  sizeY = static_cast<int>(size.second / SIZE_CASE);
  while (i < size.first)
    {
      if ((map[i] = new CollidingArea[static_cast<int>(size.second / SIZE_CASE)]) == NULL)
	errx(1, "Error : out of memory");
      ++i;
    }
}

EntityCollideLayer::~EntityCollideLayer()
{
}

void		EntityCollideLayer::setCollidingAreaData()
{
  unsigned int	x;
  unsigned int	y;

  y = 0;
  while (y < sizeY)
    {
      x = 0;
      while (x < sizeX)
	{
	  map[y][x].posx = x * SIZE_CASE;
	  map[y][x].posy = y * SIZE_CASE;
	  map[y][x].sizex = (x + 1) * SIZE_CASE - 0.01;
	  map[y][x].sizex = (y + 1) * SIZE_CASE - 0.01;
	  ++x;
	}
      ++y;
    }
}

bool		EntityCollideLayer::canMovePoint(double posx, double posy)
{
  int		x;
  int		y;
  std::list<gauntlet::ABody*>::iterator	it1;
  std::pair<double, double>	pos;
  std::pair<double, double>	size;

  x = static_cast<int>(posx / SIZE_CASE);
  y = static_cast<int>(posy / SIZE_CASE);
  it1 = map[y][x].Entity.begin();
  while (it1 != map[y][x].Entity.end())
    {
      pos = (*it1)->getPos();
      size = (*it1)->getSize();
      if (posx >= pos.first && posx <= pos.first + size.first
	  && posy >= pos.second && posy <= pos.second + size.second)
	return (false);
      it1++;
    }
  return (true);
}

bool		EntityCollideLayer::tryMoveId(int id, double posx, double posy)
{
  int		x;
  int		y;
  std::list<gauntlet::ABody*>::iterator	it1;
  std::pair<double, double>		pos;
  std::pair<double, double>		size;

  it1 = Entity.begin();
  while (it1 != Entity.end())
    {
      if ((*it1)->getId() == id)
	{
	  pos = (*it1)->getPos();
	  size = (*it1)->getSize();
	  x = static_cast<int>(pos.first / SIZE_CASE);
	  y = static_cast<int>(pos.second / SIZE_CASE);
	  if ((static_cast<int>(posx / SIZE_CASE) != x
	       || static_cast<int>(posy / SIZE_CASE) != y)
	      && canMovePoint(pos.first, pos.second) == true
	      && canMovePoint(pos.first + size.first, pos.second) == true
	      && canMovePoint(pos.first, pos.second + size.second) == true
	      && canMovePoint(pos.first + size.first, pos.second + size.second) == true)
	    {
	      map[static_cast<int>(posy / SIZE_CASE)]
		[static_cast<int>(posy / SIZE_CASE)]
		.Entity.push_front(*it1);
	      suprMapId(id, x, y);
	      return (true);
	    }
	  return (false);
	}
    }
  return (false);
}

void		EntityCollideLayer::suprMapId(int id, int x, int y)
{
  std::list<gauntlet::ABody*>::iterator	it1;

  it1 = map[y][x].Entity.begin();
  while (it1 != map[y][x].Entity.end())
    {
      if ((*it1)->getId() == id)
	{
	  map[y][x].Entity.erase(it1);
	  break;
	}
      it1++;
    }
}

void		EntityCollideLayer::suprId(int id)
{
  std::list<gauntlet::ABody*>::iterator	it1;
  int				x;
  int				y;

  it1 = Entity.begin();
  while (it1 != Entity.end())
    {
      if ((*it1)->getId() == id)
	{
	  x = static_cast<int>((*it1)->getPos().first / SIZE_CASE);
	  y = static_cast<int>((*it1)->getPos().second / SIZE_CASE);
	  suprMapId(id, x, y);
	  Entity.erase(it1);
	  break;
	}
      it1++;
    }
}

bool		EntityCollideLayer::setNewBody(gauntlet::ABody *newBody)
{
  std::pair<double, double>	pos;
  std::pair<double, double>	size;
  int				x;
  int				y;

  pos = newBody->getPos();
  size = newBody->getSize();
  x = static_cast<int>(pos.first / SIZE_CASE);
  y = static_cast<int>(pos.second / SIZE_CASE);
  if (canMovePoint(pos.first, pos.second) == true
      && canMovePoint(pos.first + size.first, pos.second) == true
      && canMovePoint(pos.first, pos.second + size.second) == true
      && canMovePoint(pos.first + size.first, pos.second + size.second) == true)
    {
      Entity.push_front(newBody);
      map[y][x].Entity.push_front(newBody);
      return(true);
    }
  return (false);
}

std::vector<gauntlet::ABody*>	EntityCollideLayer::giveBodyInAreaCircle(double posx, double posy, double rayon)
{
  
}

std::vector<gauntlet::ABody*>	EntityCollideLayer::giveBodyInAreaCone(double posx, double posy, double size, short angle)
{
  
}
