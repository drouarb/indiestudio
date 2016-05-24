//
// BodyFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 16:50:32 2016 Alexis Trouve
// Last update Tue May 24 11:36:17 2016 Alexis Trouve
//

#include <iostream>
#include <gameData/Spell/SpellFactory.hh>
#include <gameData/TextureName.hh>
#include "BodyFactory.hh"

using namespace gauntlet;

BodyFactory::BodyFactory()
{}

BodyFactory::BodyFactory(world::World *nworld, std::vector<world::AbstractAI*>& nAIs)
{
  world = nworld;
  AIs = nAIs;
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
  setWizard();
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
  player->spellBook.addSpell(SpellFactory::BARBARIAN_ATTACK, player);
  player->spellBook.addSpell(SpellFactory::BARBARIAN_TORNADO, player);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(10.0, 10.0));
  player->changeOrientation(0);
  player->setModel(EntityName::NINJA);
  player->setTexture(TextureName::NINjA_M);
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
  player->setModel(EntityName::NINJA);
  player->setTexture(TextureName::NINjA_M);
  bodyTab.push_back(player);
}

void			BodyFactory::setWizard()
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
  player->setModel(EntityName::NINJA);
  player->setTexture(TextureName::NINjA_M);
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
  player->spellBook.addSpell(SpellFactory::VALKYRIA_ATTACK, player);
  player->spellBook.addSpell(SpellFactory::VALKYRIA_DASH, player);
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(10.0, 10.0));
  player->changeOrientation(0);
  player->setModel(EntityName::NINJA);
  player->setTexture(TextureName::NINjA_M);
  bodyTab.push_back(player);
}

void			BodyFactory::setDraugr()
{
  unsigned int		i;
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("Draugr");
  crea->stats.HP = 1000;
  crea->stats.normalHP = 1000;
  crea->stats.speed = 1.0;
  crea->stats.normalSpeed = 1.0;
  crea->stats.attackModifier = 1.0;
  crea->spellBook.addSpell(SpellFactory::DRAUGR_ATTACK, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(10.0, 10.0));
  crea->changeOrientation(0);
  crea->setModel(EntityName::NINJA);
  crea->setTexture(TextureName::NINjA_M);
  crea->setTexture(1);
  bodyTab.push_back(crea);
  i = 0;
  while (i < AIs.size())
    {
      if (AIs[i]->getName() == "BasicAI")
	AIs[i]->setNewAI(crea);
      ++i;
    }
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
