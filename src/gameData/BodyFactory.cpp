//
// BodyFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 16:50:32 2016 Alexis Trouve
// Last update Fri May 27 13:26:40 2016 Alexis Trouve
//

#include <iostream>
#include <gameData/Spell/SpellFactory.hh>
#include <gameData/TextureName.hh>

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
  setDoor();
  setKey();
}

void			BodyFactory::setBarbare()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Barbare");
  player->stats.HP = 4000;
  player->stats.normalHP = 4000;
  player->stats.speed = 1.1;
  player->stats.normalSpeed = 1.1;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->spellBook.addSpell(SpellFactory::BARBARIAN_ATTACK, player);
  player->spellBook.addSpell(SpellFactory::BARBARIAN_TORNADO, player);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(80.0, 80.0));
  player->changeOrientation(90);
  player->setMeshId(EntityName::BERSERK);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setElf()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Elf");
  player->stats.HP = 3000;
  player->stats.normalHP = 3000;
  player->stats.speed = 1.4;
  player->stats.normalSpeed = 1.4;
  player->stats.attackModifier = 1.0;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(80.0, 80.0));
  player->changeOrientation(0);
  player->setMeshId(EntityName::BERSERK);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setWizard()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Mage");
  player->stats.HP = 1000;
  player->stats.normalHP = 1000;
  player->stats.speed = 1.2;
  player->stats.normalSpeed = 1.2;
  player->stats.attackModifier = 1.2;
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(80.0, 80.0));
  player->changeOrientation(0);
  player->setMeshId(EntityName::BERSERK);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setValkyrie()
{
  Player		*player;

  player = new Player(-1, world);
  player->setName("Valkyrie");
  player->stats.HP = 5000;
  player->stats.normalHP = 5000;
  player->stats.speed = 0.9;
  player->stats.normalSpeed = 0.9;
  player->stats.attackModifier = 1.0;
  player->spellBook.addSpell(SpellFactory::VALKYRIA_ATTACK, player);
  player->spellBook.addSpell(SpellFactory::VALKYRIA_DASH, player);
  player->setCollide(true);
  player->changePos(std::make_pair(-1, -1));
  player->changeSize(std::make_pair(100.0, 100.0));
  player->changeOrientation(0);
  player->setMeshId(EntityName::BERSERK);
  player->setTextureId(TextureName::TEXTURE_NONE);
  player->setIdAI(NOAI);
  bodyTab.push_back(player);
}

void			BodyFactory::setDraugr()
{
  unsigned int		i;
  Creature		*crea;

  crea = new Creature(-1, world);
  crea->setName("Draugr");
  crea->stats.HP = 400;
  crea->stats.normalHP = 400;
  crea->stats.speed = 0.6;
  crea->stats.normalSpeed = 0.6;
  crea->stats.attackModifier = 0.6;
  crea->spellBook.addSpell(SpellFactory::DRAUGR_ATTACK, crea);
  crea->setCollide(true);
  crea->changePos(std::make_pair(-1, -1));
  crea->changeSize(std::make_pair(50.0, 50.0));
  crea->changeOrientation(0);
  crea->setMeshId(EntityName::BERSERK);
  crea->setTextureId(TextureName::TEXTURE_NONE);
  crea->setIdAI(MELEEBASICAI);
  bodyTab.push_back(crea);
  i = 0;
  while (i < AIs.size())
    {
      if (AIs[i]->getName() == "BasicAI")
	AIs[i]->setNewAI(crea);
      ++i;
    }
}

void            BodyFactory::setKey()
{
  GameObject		*obj;
  Item              *key;

  key = new Item();
  key->setKey(true);
  obj = new GameObject(-1, world);
  obj->setBasicParameters("Key", true, false);
  obj->setCollide(false);
  obj->setMeshId(EntityName::CHEST);
  obj->setTextureId(EntityName::CHEST);
  obj->addItem(*key);
  bodyTab.push_back(obj);
}

void            BodyFactory::setDoor()
{
  GameObject        *obj;

  obj = new GameObject(-1, world);
  obj->setBasicParameters("Door", false, true);
  obj->setCollide(true);
  obj->setMeshId(EntityName::DOOR);
  obj->setTextureId(EntityName::DOOR);
  bodyTab.push_back(obj);
}

void			BodyFactory::setPorteLight()
{
  GameObject		*obj;

  obj = new GameObject(-1, world);
  obj->setName("PorteLight");
  obj->setCollide(true);
  obj->changePos(std::make_pair(-1, -1));
  obj->changeSize(std::make_pair(160.0, 160.0));
  obj->changeOrientation(0);
  bodyTab.push_back(obj);
}

ABody	*BodyFactory::giveBody(const std::string& name)
{
  unsigned int	i;
  ABody		*body;
  Actor		*actor;

  i = 0;
  while (i < bodyTab.size())
    {
      if (name == bodyTab[i]->getName())
	{
	  body = bodyTab[i]->clone(giveNextId());
	  if ((actor = dynamic_cast<Actor*>(body)) != NULL)
	    {
	      i = actor->getIdAI();
	      if (i != NOAI)
		AIs[i]->setNewAI(actor);
	    }
	  return (body);
	}
      ++i;
    }
  return (NULL);
}
