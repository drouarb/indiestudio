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
  items = new ItemContainer();
}

GameObject::~GameObject()
{
  delete(items); //newItemContainer gameObject();
}

void        GameObject::gather(ItemContainer *curInventory)
{
  if (gatherable)
  {
    curInventory->operator+=(this->items);
    world->notifyDeath(this);
  }
}

void        GameObject::open(ItemContainer *curInventory) //unfinished
{
  if (openable) {
    std::list<Item> *inv = curInventory->getItemList();
    for (auto item: *inv) {
      if (item.isKey())
      {
        inv->remove(item);
        world->notifyDeath(this);
        break;
      }
    }
  }
}

void        *GameObject::setBasicParameters(std::string _name, bool _gatherable, bool _openable)
{
  name = _name;
  gatherable = _gatherable;
  openable = _openable;
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
  obj->openable = this->openable;
  return (obj);
}

void GameObject::addItem(Item item) {
  items->getItemList()->push_back(item);
}


