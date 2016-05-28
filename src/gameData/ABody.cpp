//
// ABody.cpp for ABody in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:07:25 2016 Alexis Trouve
// Last update Fri May 27 22:32:14 2016 Alexis Trouve
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
  model = 0;
  texture = 0;
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

std::pair<double, double>	ABody::pointInFront(double dist)
{
  return (std::pair<double, double>
	  (coord.first + dist * world::Math::cos(orientation),
	   coord.second + dist * world::Math::sin(orientation)));
}

world::World *ABody::getWorld() {
  return world;
}

unsigned int			ABody::getEntityId() const
{
  return (id);
}

unsigned int			ABody::getTextureId() const
{
  return (texture);
}

unsigned int			ABody::getMeshId() const
{
  return (model);
}

void                    ABody::setMeshId(int _model)
{
  model = _model;
}

void                    ABody::setTextureId(int _texture)
{
  texture = _texture;
}

void                    ABody::setTextureId()
{
  texture = 0;
}

void                    ABody::setCooldown(unsigned long _cooldown)
{
  cooldown = world->turn + _cooldown;
}

bool ABody::recharged() {
  return (world->turn > cooldown);
}


