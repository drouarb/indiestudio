//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Sun May 29 15:58:52 2016 Esteban Lewis
//

#include <iostream>
#include <stdexcept>
#include "world/PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(const std::string& filePath)
{
  if (!heightmap.load(filePath))
    throw (std::runtime_error("Wrong height map"));
  sizeX = heightmap.getSize().first;
  sizeY = heightmap.getSize().second;
}

PhysicCollideLayer::~PhysicCollideLayer()
{}

std::pair<double, double>    PhysicCollideLayer::getSize() const
{
  return (std::make_pair(sizeX, sizeY));
}

bool PhysicCollideLayer::isWall(const std::pair<double, double>& oldPos,
				const std::pair<double, double>& wantedPos)
{
  return (ABS(heightmap.at(oldPos.first, oldPos.second) -
	      heightmap.at(wantedPos.first, wantedPos.second)) >= WALL_MIN_HEIGHT);
}

bool    PhysicCollideLayer::checkCoordSizeCanPass(const std::pair<double, double>& oldPos,
						  const std::pair<double, double>& wantedPos,
						  const std::pair<double, double>& size)
{
  if (oldPos.first == wantedPos.first && oldPos.second == wantedPos.second)
    return (true);

  std::pair<double, double> start;
  std::pair<double, double> end;

  start.second = oldPos.second + size.second / 2;
  end.second = oldPos.second - size.second / 2;
  if (oldPos.second < wantedPos.second)
    {
      if (oldPos.first < wantedPos.first)
	{
	  start.first = oldPos.first - size.first / 2;
	  end.first = oldPos.first + size.first / 2;
	}
      else
	{
	  start.first = oldPos.first + size.first / 2;
	  end.first = oldPos.first - size.first / 2;
	}
    }
  else
    {
      if (oldPos.first < wantedPos.first)
	{
	  start.first = oldPos.first + size.first / 2;
	  end.first = oldPos.first - size.first / 2;
	}
      else
	{
	  start.first = oldPos.first - size.first / 2;
	  end.first = oldPos.first + size.first / 2;
	}
    }

  if (ABS(oldPos.first - wantedPos.first) > ABS(oldPos.second - wantedPos.second))
    {
      inc.first = (oldPos.first < wantedPos.first ? 1 : -1);
      inc.second = ABS((oldPos.second - wantedPos.second) /
		       (oldPos.first - wantedPos.first));
      if (oldPos.second > wantedPos.second)
	inc.second *= -1;
      nb_points = ABS((oldPos.first - wantedPos.first) / inc.first);
    }
  else
    {
      inc.second = (oldPos.second < wantedPos.second ? 1 : -1);
      inc.first = ABS((oldPos.first - wantedPos.first) /
		      (oldPos.second - wantedPos.second));
      if (oldPos.first > wantedPos.first)
	inc.first *= -1;
      nb_points = ABS((oldPos.second - wantedPos.second) / inc.second);
    }

  return (doOnLine(start, end, &PhysicCollideLayer::checkLine, true));
}

bool PhysicCollideLayer::doOnLine(std::pair<double, double> start,
				  std::pair <double, double> end,
				  bool (PhysicCollideLayer::*func)
				  (std::pair<double, double>),
				  bool divide)
{
  double inc_y;
  double inc_x;

  if (ABS(start.first - end.first) > ABS(start.second - end.second))
    {
      inc_y = ABS((end.second - start.second) / (end.first - start.first));
      if (start.second > end.second)
	inc_y *= -1;
      inc_x = (start.first < end.first ? 1 : -1);
      if (divide)
	{
	  inc_y *= POINTNBDIVIDER;
	  inc_x *= POINTNBDIVIDER;
	}

      if (start.first < end.first)
        while (start.first <= end.first)
          {
            if (!(this->*func)(start))
	      return (false);
            start.second += inc_y;
            start.first += inc_x;
          }
      else
        while (start.first >= end.first)
          {
            if (!(this->*func)(start))
	      return (false);
            start.second += inc_y;
            start.first += inc_x;
          }
    }
  else
    {
      inc_y = (start.second < end.second ? 1 : -1);
      inc_x = ABS((end.first - start.first) / (end.second - start.second));
      if (start.first > end.first)
	inc_x *= -1;
      if (divide)
	{
	  inc_y *= POINTNBDIVIDER;
	  inc_x *= POINTNBDIVIDER;
	}

      if (start.second < end.second)
        while (start.second <= end.second)
          {
            if (!(this->*func)(start))
	      return (false);
            start.second += inc_y;
            start.first += inc_x;
          }
      else
        while (start.second >= end.second)
          {
            if (!(this->*func)(start))
	      return (false);
            start.second += inc_y;
            start.first += inc_x;
          }
    }
  return (true);
}

bool PhysicCollideLayer::checkLine(std::pair<double, double> point)
{
  lastPoint = point;
  std::pair<double, double> dest;
  dest.first = point.first + inc.first * nb_points;
  dest.second = point.second + inc.second * nb_points;

  if (point.first < 0 || point.first >= sizeX ||
      point.second < 0 || point.second >= sizeY ||
      dest.first < 0 || dest.first >= sizeX ||
      dest.second < 0 || dest.second >= sizeY)
    return (false);

  return (doOnLine(point, dest, &PhysicCollideLayer::checkPoint, false));
}

bool PhysicCollideLayer::checkPoint(std::pair<double, double> point)
{
  if (isWall(lastPoint, point))
    return (false);
  lastPoint = point;
  return (true);
}

const unsigned char *PhysicCollideLayer::getLayer() const
{
  return (layer);
}
