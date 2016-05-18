//
// EntityCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 11:03:19 2016 Alexis Trouve
// Last update Wed May 18 13:30:35 2016 Alexis Trouve
//

#include <iostream>
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
	  map[y][x].sizex = SIZE_CASE;
	  map[y][x].sizex = SIZE_CASE;
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

double		EntityCollideLayer::getDist(double refx, double refy,
					    const ABody &target)
{
  return (sqrt(pow(target.getPos().first - refx, 2) +
	       pow(target.getPos().second - refy, 2)));
}

int		EntityCollideLayer::getAngle(double refx, double refy,
					     int refa, const ABody & target)
{
  return (Math::getAngle(-atan2((target.getPos().second - refy),
				(target.getPos().first - refx))) - refa);
}

std::list<gauntlet::ABody*>	EntityCollideLayer::giveBodyInAreaCircle(double posx, double posy, double rayon)
{
  std::list<ABody*>		list;

  long max_x = (int)((posx + rayon) / SIZE_CASE);
  long max_y = (int)((posy + rayon) / SIZE_CASE);
  long min_x = (int)((posx - rayon) / SIZE_CASE);
  long min_y = (int)((posy - rayon) / SIZE_CASE);

  if (max_x >= sizeX)
    max_x = sizeX - 1;
  if (max_y >= sizeY)
    max_y = sizeY - 1;
  if (min_x < 0)
    min_x = 0;
  if (min_y < 0)
    min_y = 0;

  int it_x = min_x;
  while (it_x <= max_x)
    {
      int it_y = min_y;
      while (it_y <= max_y)
	{
	  for (std::list<ABody*>::const_iterator it = map[it_x][it_y].Entity.begin();
	       it != map[it_x][it_y].Entity.end(); ++it)
	    {
	      if (getDist(posx, posy, **it) < rayon)
		list.push_back(*it);
	    }
	  it_y++;
	}
      it_x++;
    }
  return (list);
}

std::list<gauntlet::ABody*>	EntityCollideLayer::giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  short halfangle = cone_angle / 2;
  std::list<ABody*>		list = giveBodyInAreaCircle(posx, posy, size);
  for (std::list<ABody*>::iterator it = list.begin(); it != list.end(); ++it)
    {
      short res = getAngle(posx, posy, ref_angle, **it);
      std::cout << "target " << (*it)->getId() << " -> " << res << std::endl;
      if (!Math::isBetween(res, halfangle, -halfangle))
	{
	  it = list.erase(it);
	  --it;
	}
    }
  return (list);
}
