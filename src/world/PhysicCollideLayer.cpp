//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Fri May 13 11:24:47 2016 Alexis Trouve
//

#include "PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer()
{
  sizeX = 0;
  sizeY = 0;
}

PhysicCollideLayer::~PhysicCollideLayer()
{

}

std::pair<double, double>	PhysicCollideLayer::getSize()
{
  return (std::make_pair(sizeX, sizeY));
}
