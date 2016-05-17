//
// PhysicCollideLayer.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 16:17:25 2016 Alexis Trouve
// Last update Sat May 14 12:12:55 2016 Alexis Trouve
//

#include "PhysicCollideLayer.hh"

using namespace gauntlet;
using namespace world;

PhysicCollideLayer::PhysicCollideLayer(double sizex, double sizey)
{
  sizeX = sizex;
  sizeY = sizey;
}

PhysicCollideLayer::~PhysicCollideLayer()
{

}

std::pair<double, double>	PhysicCollideLayer::getSize()
{
  return (std::make_pair(sizeX, sizeY));
}
