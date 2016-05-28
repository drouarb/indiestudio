//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Sat May 28 16:24:36 2016 Alexis Trouve
//

#include <iostream>
#include "world/PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(const std::string& filePath)
{
}

PhysicCollideLayer::~PhysicCollideLayer()
{}

std::pair<double, double>    PhysicCollideLayer::getSize() const
{
  return (std::make_pair(sizeX, sizeY));
}

bool PhysicCollideLayer::isWall(const std::pair<double, double>& oldPos, const std::pair<double, double>& wantedPos)
{
  return (true);
}

bool    PhysicCollideLayer::checkCoordSizeCanPass(const std::pair<double, double>& oldPos,
						  const std::pair<double, double>& wantedPos,
						  const std::pair<double, double>& size)
{
  return (true);
}

const unsigned char *PhysicCollideLayer::getLayer(int nb) const
{
  return (layer);
}
