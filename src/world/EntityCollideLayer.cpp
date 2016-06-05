#include <iostream>
#include "EntityCollideLayer.hh"
#include "ScopedLock.hpp"

using namespace gauntlet;
using namespace world;

EntityCollideLayer::EntityCollideLayer(gauntlet::world::PhysicCollideLayer *physicLayer)
{
  unsigned int			i;
  std::pair<double, double>	size;

  size = physicLayer->getSize();
  i = 0;
  sizeX = static_cast<int>(size.first / SIZE_CASE + 1);
  sizeY = static_cast<int>(size.second / SIZE_CASE + 1);
  if ((map = new CollidingArea*[static_cast<int>(sizeY)]) == NULL)
    exit(1);
  while (i < sizeY)
    {
      if ((map[i] = new CollidingArea[static_cast<int>(sizeX)]) == NULL)
	exit(1);
      ++i;
    }
}

EntityCollideLayer::~EntityCollideLayer()
{
}

std::list<ABody*>	EntityCollideLayer::getCollideBody()
{
  std::list<ABody*>		listend;
  std::list<ABody*>		resCircle;
  std::list<ABody*>::iterator	it1;
  std::list<ABody*>::iterator	it2;
  std::list<ABody*>::iterator	it3;
  int				x;
  int				y;
  ScopedLock				lock(&mutex);

  it1 = Entity.begin();
  while (it1 != Entity.end())
    {
      resCircle = giveBodyInAreaCircle((*it1)->getPos().first, (*it1)->getPos().second,
				       (*it1)->getSize().first - ((*it1)->getSize().first / 4));
      it2 = resCircle.begin();
      while (it2 != resCircle.end())
	{
	  if ((*it2)->getId() == (*it1)->getId())
	    {
	      resCircle.erase(it2);
	      break;
	    }
	  it2++;
	}
      it2 = resCircle.begin();
      if (resCircle.size() > 0)
	while (it2 != resCircle.end())
	  {
	    if (listend.size() > 0)
	      {
		it3 = listend.begin();
		while (it3 != listend.end())
		  {
		    if ((*it3)->getId() == (*it2)->getId())
		      break;
		    it3++;
		  }
		if (it3 == listend.end())
		  listend.push_back((*it2));
	      }
	    else
	      listend.push_back((*it2));
	    it2++;
	  }
      it1++;
    }
  return (listend);
}

void		EntityCollideLayer::setCollidingAreaData()
{
  unsigned int	x;
  unsigned int	y;
  ScopedLock				lock(&mutex);

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

bool		EntityCollideLayer::tryMoveId(int id, double posx, double posy)
{
  int		x;
  int		y;
  std::list<gauntlet::ABody*>::iterator	it1;
  std::pair<double, double>		pos;
  std::pair<double, double>		size;
  ScopedLock				lock(&mutex);

  it1 = Entity.begin();
  while (it1 != Entity.end())
    {
      if ((*it1)->getId() == id)
	{
	  pos = (*it1)->getPos();
	  size = (*it1)->getSize();
	  if (giveBodyInAreaCircle(posx, posy, (*it1)->getSize().first + 2.0).size() <= 1)
	      {
		x = static_cast<int>(pos.first / SIZE_CASE);
		y = static_cast<int>(pos.second / SIZE_CASE);
		if (x != static_cast<int>(posx / SIZE_CASE) || y != static_cast<int>(posy / SIZE_CASE))
		  {
		    map[static_cast<int>(posy / SIZE_CASE)]
		      [static_cast<int>(posx / SIZE_CASE)]
		      .Entity.push_front(*it1);
		    suprMapId(id, x, y);
		  }
		(*it1)->changePos(std::make_pair(posx, posy));
		return (true);
	      }
	  return (false);
	}
      it1++;
    }
  return (false);
}

void		EntityCollideLayer::forceMoveId(int id, double posx, double posy)
{
  int		x;
  int		y;
  std::list<gauntlet::ABody*>::iterator	it1;
  std::pair<double, double>		pos;
  std::pair<double, double>		size;
  ScopedLock				lock(&mutex);

  it1 = Entity.begin();
  while (it1 != Entity.end())
    {
      if ((*it1)->getId() == id)
	{
	  pos = (*it1)->getPos();
	  size = (*it1)->getSize();
	  x = static_cast<int>(pos.first / SIZE_CASE);
	  y = static_cast<int>(pos.second / SIZE_CASE);
	  if (x != static_cast<int>(posx / SIZE_CASE) || y != static_cast<int>(posy / SIZE_CASE))
	    {
	      map[static_cast<int>(posy / SIZE_CASE)]
		[static_cast<int>(posx / SIZE_CASE)]
		.Entity.push_front(*it1);
	      suprMapId(id, x, y);
	    }
	  (*it1)->changePos(std::make_pair(posx, posy));
	  break;
	}
      it1++;
    }
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
  ScopedLock				lock(&mutex);

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
  ScopedLock				lock(&mutex);

  pos = newBody->getPos();
  size = newBody->getSize();
  x = static_cast<int>(pos.first / SIZE_CASE);
  y = static_cast<int>(pos.second / SIZE_CASE);
  if (giveBodyInAreaCircle(newBody->getPos().second, newBody->getPos().second, newBody->getSize().first + 2.0).size() <= 1)
    {
      Entity.push_front(newBody);
      map[y][x].Entity.push_front(newBody);
      return(true);
    }
  return (false);
}

void		EntityCollideLayer::forceSetBody(gauntlet::ABody *newBody)
{
  std::pair<double, double>	pos;
  std::pair<double, double>	size;
  int				x;
  int				y;
  ScopedLock				lock(&mutex);

  pos = newBody->getPos();
  size = newBody->getSize();
  x = static_cast<int>(pos.first / SIZE_CASE);
  y = static_cast<int>(pos.second / SIZE_CASE);
  Entity.push_front(newBody);
  map[y][x].Entity.push_front(newBody);
}

double		EntityCollideLayer::getDist(double refx, double refy,
					    const ABody &target)
{
  double dist = sqrt(pow(target.getPos().first - refx, 2) +
		     pow(target.getPos().second - refy, 2));
  if (target.getSize().first == 0 || target.getSize().second == 0)
    return (dist);

  short angle = Math::getAngle(atan2((target.getPos().second - refy),
				       (refx - target.getPos().first)) + M_PI);
  short a1 =
    Math::getAngle(-atan2(target.getSize().second / 2, -target.getSize().first / 2));
  short a2 = 
    Math::getAngle(-atan2(target.getSize().second / 2, target.getSize().first / 2));
  short a3 = 
    Math::getAngle(-atan2(-target.getSize().second / 2, target.getSize().first / 2));
  short a4 = 
    Math::getAngle(-atan2(-target.getSize().second / 2, -target.getSize().first / 2));

  double proportion;
  if (Math::isBetween(angle, a2, a1) || Math::isBetween(angle, a4, a3))
    {
      //top or bottom side
      proportion = target.getSize().second / 2 / (target.getPos().second - refy);
    }
  else
    {
      //left or right side
      proportion = target.getSize().first / 2 / (target.getPos().first - refx);
    }
  if (proportion < 0)
    proportion = -proportion;
  if (proportion > 1)
    return (dist);
  return (dist - dist * proportion);
}

int		EntityCollideLayer::getAngle(double refx, double refy,
					     int refa, const ABody & target)
{
  return (Math::getAngle(atan2((target.getPos().second - refy),
				(refx - target.getPos().first))) - refa);
}

bool				EntityCollideLayer::bodyLineIntersection(double refX,
									 double refY,
									 short angle,
									 double bodySizeX,
									 double bodySizeY,
									 ABody & body)
{
  double			a1, b1; //reference half-line equation
  double			a2, b2; //body line equation
  a1 = Math::sin(angle) / Math::cos(angle);
  b1 = refY - a1 * refX;
  a2 = -bodySizeY / bodySizeX;
  b2 = body.getPos().second - a2 * body.getPos().first;

  if (a1 - a2 == 0)
    {
      //parallel lines
      return (false);
    }

  //intersection point
  double x = (b2 - b1) / (a1 - a2);
  double y = a2 * x + b2;

  if (!(x >= body.getPos().first - body.getSize().first / 2 &&
	x <= body.getPos().first + body.getSize().first / 2 &&
	y >= body.getPos().second - body.getSize().second / 2 &&
	y <= body.getPos().second + body.getSize().second / 2))
    {
      //point not in body hitbox
      return (false);
    }
  if (!((Math::isBetween(angle, Math::A_RIGHT, Math::A_RIGHT_NEG) && x >= refX) ||
	(Math::isBetween(angle, Math::A_RIGHT_NEG, Math::A_RIGHT) && x <= refX)))
    {
      //point not on cone side of line
      return (false);
    }
  return (true);
}

std::list<gauntlet::ABody*>	EntityCollideLayer::giveBodyInAreaCircle(double posx, double posy, double rayon)
{
  std::list<ABody*>		list;

  long max_x = (int)((posx + rayon) / SIZE_CASE);
  long max_y = (int)((posy + rayon) / SIZE_CASE);
  long min_x = (int)((posx - rayon) / SIZE_CASE);
  long min_y = (int)((posy - rayon) / SIZE_CASE);

  if (max_x >= (int)sizeX)
    max_x = sizeX - 1;
  if (max_y >= (int)sizeY)
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
	  for (std::list<ABody*>::const_iterator it = map[it_y][it_x].Entity.begin();
	       it != map[it_y][it_x].Entity.end(); ++it)
	    {
	      if (getDist(posx, posy, **it) <= rayon)
		list.push_back(*it);
	    }
	  it_y++;
	}
      it_x++;
    }
  return (list);
}

std::list<gauntlet::ABody*> EntityCollideLayer::giveBodyInAreaRectangle(double posx, double posy, short ratio, double size, short unused)
{
    //ratio == ratio entre x et y -> 3 par exemple si size (x) = 4 dans ce cas là y = 12
    //tracer trois ligne une sur chaque bord
    return (std::list<gauntlet::ABody*>());
}

std::list<gauntlet::ABody*>	EntityCollideLayer::giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle)
{
  short halfangle = cone_angle / 2;
  std::list<ABody*>		list = giveBodyInAreaCircle(posx, posy, size);
  for (std::list<ABody*>::iterator it = list.begin(); it != list.end(); ++it)
    {
      short res = getAngle(posx, posy, ref_angle, **it);
      if (!(Math::isBetween(res, halfangle, -halfangle) ||
	    (bodyLineIntersection(posx, posy, ref_angle + halfangle,
				  (*it)->getSize().first / 2,
				  (*it)->getSize().second / 2, **it) ||
	     bodyLineIntersection(posx, posy, ref_angle + halfangle,
				  -(*it)->getSize().first / 2,
				  (*it)->getSize().second / 2, **it) ||
	     bodyLineIntersection(posx, posy, ref_angle - halfangle,
				  (*it)->getSize().first / 2,
				  (*it)->getSize().second / 2, **it) ||
	     bodyLineIntersection(posx, posy, ref_angle - halfangle,
				  -(*it)->getSize().first / 2,
				  (*it)->getSize().second / 2, **it))))
	{
	  it = list.erase(it);
	  --it;
	}
    }
  return (list);
}

ABody			*EntityCollideLayer::getBodyId(int id)
{
  std::list<gauntlet::ABody*>::iterator	it1;

  it1 = Entity.begin();
  while (it1 != Entity.end())
    {
      if ((*it1)->getId() == id)
	return (*it1);
      it1++;
    }
  return (NULL);
}
