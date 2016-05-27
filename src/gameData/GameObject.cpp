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
#include "World.hh"

using namespace gauntlet;

GameObject::GameObject(int nid, world::World *nworld)
  : ABody(nid)
{
  world = nworld;
  gatherable = false;
  openable = false;
}

GameObject::~GameObject()
{
}

void        GameObject::gather(ItemContainer *curInventory)
{
  if (gatherable)
  {
    world->notifyDeath(this);
    curInventory->operator+=(this->items);
  }
}

void        GameObject::open(ItemContainer *curInventory) //unfinished
{
  if (openable) {
    std::list<Item> *inv = curInventory->getItemList();
    for (auto item: *inv) {
      if (item.isKey())
      {
        world->notifyDeath(this);
        inv->remove(item);
        break;
      }
    }
  }
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


