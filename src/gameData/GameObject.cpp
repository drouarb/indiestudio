//
// GameObject.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 12 17:13:51 2016 Alexis Trouve
// Last update Sun May 29 00:38:47 2016 Alexis Trouve
//

#include <iostream>
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

void        GameObject::gather(Player *player)
{
  if (gatherable)
  {
  std::cout << "MON NOM EST: " << this->name << std::endl;
    std::cout << this->name << this->items->getItemList()->size() << std::endl;
    std::cout << player->getName() << player->getInventory()->getItemList()->size() << std::endl;
    player->getInventory()->operator+=(this->items);
    std::cout << this->name << this->items->getItemList()->size() << std::endl;
    std::cout << player->getName() << player->getInventory()->getItemList()->size() << std::endl;
    player->getInventory()->useUpgrades(player);
    world->notifyDeath(this);
  }
}

void        GameObject::open(ItemContainer *curInventory) //unfinished
{
  if (openable) {
    std::cerr << "j'essaye d'ouvrir la " << this->name << std::endl;
    std::list<Item> *inv = curInventory->getItemList();
    for (auto item: *inv) {
      if (item.isKey())
      {
        std::cerr << "j'ai la clé, sort! " << std::endl;
        inv->remove(item);
        world->playSound(SoundName::DOOR_STONE, false, this->getPos());
        world->notifyDeath(this);
        this->collideActive = false;
        break;
      }
    }
  }
}

void        GameObject::setBasicParameters(std::string _name, bool _gatherable, bool _openable)
{
  name = _name;
  gatherable = _gatherable;
  openable = _openable;
}

void        GameObject::setItems(ItemContainer *itemContainer)
{
  ItemContainer itemCont;

  itemCont = *itemContainer;
  this->items = &itemCont;
}

ABody		*GameObject::clone(int id) const
{
  GameObject	*obj;

  obj = new GameObject(id, world);
  obj->setItems(this->items);
  obj->items = this->items;
  obj->setName(name);
  obj->setCollide(collideActive);
  obj->changePos(coord);
  obj->changeSize(size);
  obj->changeOrientation(orientation);
  obj->gatherable = this->gatherable;
  obj->model = this->model;
  obj->texture = this->texture;
  obj->openable = this->openable;
  return (obj);
}

void GameObject::addItem(Item item) {
  items->getItemList()->push_back(item);
  std::cout << items->getItemList()->size() << std::endl;
}


