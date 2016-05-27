//
// GameObject.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 17:13:51 2016 Alexis Trouve
// Last update Thu May 19 16:19:15 2016 Alexis Trouve
//

#include "GameObject.hh"

using namespace gauntlet;

GameObject::GameObject(int nid, world::World *nworld)
  : ABody(nid)
{
  world = nworld;
  gatherable = false;
}

GameObject::~GameObject()
{
}

ABody		*GameObject::clone(int id) const
{
  GameObject	*obj;

  obj = new GameObject(id, world);
  obj->setName(name);
  obj->setCollide(collideActive);
  obj->changePos(coord);
  obj->changeSize(size);
  obj->changeOrientation(orientation);
  obj->gatherable = this->gatherable;
  return (obj);
}
