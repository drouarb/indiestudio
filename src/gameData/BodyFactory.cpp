//
// BodyFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 16:50:32 2016 Alexis Trouve
// Last update Fri May 20 14:23:31 2016 Alexis Trouve
//

#include <iostream>
#include "BodyFactory.hh"

using namespace gauntlet;

BodyFactory::BodyFactory()
{}

BodyFactory::BodyFactory(world::World *nworld)
{
  world = nworld;
  fillCreatureTab();
  fillGameObjectTab();
  fillPlayerTab();
}

BodyFactory::~BodyFactory()
{
}

int			BodyFactory::giveNextId()
{
  static int		nextId = -1;
  
  nextId++;
  return (nextId);
}

void			BodyFactory::fillPlayerTab()
{
  setBarbare();
  setElf();
  setMage();
  setValkyrie();
}

void			BodyFactory::fillCreatureTab()
{
  setDraugr();
}

void			BodyFactory::fillGameObjectTab()
{
  setPorteLight();
}

void			BodyFactory::setBarbare()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Barbare");
  player->stats.HP = 1000;
  player->stats.normalHP = 1000;
  player->stats.speed = 1.0;
  player->stats.normalSpeed = 1.0;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(10.0, 10.0));
  player->changeOrientation(0);
  bodyTab.push_back(player);
}

void			BodyFactory::setElf()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Elf");
  player->stats.HP = 1000;
  player->stats.normalHP = 1000;
  player->stats.speed = 1.0;
  player->stats.normalSpeed = 1.0;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(10.0, 10.0));
  player->changeOrientation(0);
  bodyTab.push_back(player);
}

void			BodyFactory::setMage()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Mage");
  player->stats.HP = 1000;
  player->stats.normalHP = 1000;
  player->stats.speed = 1.0;
  player->stats.normalSpeed = 1.0;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(10.0, 10.0));
  player->changeOrientation(0);
  bodyTab.push_back(player);
}

void			BodyFactory::setValkyrie()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Valkyrie");
  player->stats.HP = 1000;
  player->stats.normalHP = 1000;
  player->stats.speed = 1.0;
  player->stats.normalSpeed = 1.0;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(10.0, 10.0));
  player->changeOrientation(0);
  bodyTab.push_back(player);
}

void			BodyFactory::setDraugr()
{
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("Draugr");
  crea->stats.HP = 1000;
  crea->stats.normalHP = 1000;
  crea->stats.speed = 1.0;
  crea->stats.normalSpeed = 1.0;
  crea->stats.attackModifier = 1.0;
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(10.0, 10.0));
  crea->changeOrientation(0);
  bodyTab.push_back(crea);
}

void			BodyFactory::setPorteLight()
{
  GameObject		*obj;

  obj = new GameObject(-1, world);
  obj->setName("PorteLight");
  obj->setCollide(true);
  obj->changePos(std::make_pair(-1, -1));
  obj->changeSize(std::make_pair(20.0, 20.0));
  obj->changeOrientation(0);
  bodyTab.push_back(obj);
}

ABody	*BodyFactory::giveBody(const std::string& name)
{
  unsigned int	i;

  i = 0;
  while (i < bodyTab.size())
    {
      if (name == bodyTab[i]->getName())
	return (bodyTab[i]->clone(giveNextId()));
      ++i;
    }
  return (NULL);
}
