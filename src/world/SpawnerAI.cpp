//
// SpawnerAI.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
//
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
//
// Started on  Sun May 22 11:46:42 2016 Alexis Trouve
// Last update Sat Jun  4 19:08:08 2016 Alexis Trouve
//

#include <iostream>
#include "SpawnerAI.hh"
#include "World.hh"
#include "Spell.hh"

using namespace gauntlet;
using namespace world;

SpawnerAI::SpawnerAI(World *nworld) : AbstractAI(nworld)
{
    nameAI = "SpawnerAI";
}

SpawnerAI::~SpawnerAI()
{
}

int        SpawnerAI::launchAI(std::pair<double, double> pos)
{
  unsigned int i;
  int nbrPlayed;

 i = 0;
  nbrPlayed = 0;
  while (i < actors.size())
    {
      if (actors[i]->stats.HP > 0 &&
	  Math::distBetween(pos, actors[i]->getPos()) < AI_LAUNCH_DIST)
	{
	  launchAI(actors[i]);
	  nbrPlayed += 1;
	}
      else
	{
	  if (actors[i]->getMove())
	    actors[i]->setMove();
	}
      ++i;
    }
  return (nbrPlayed);
}

void            SpawnerAI::launchAI(gauntlet::Actor *actor)
{
  Spawner	*me;
  std::pair<double, double>	pos;
  std::list<ABody *> bodys;
  std::list<ABody *>::iterator it1;
  Player *savedPlayer;
  Player *tmpPlayer;
  int idAttack;
  
  if ((me = dynamic_cast<Spawner*>(actor)) != NULL)
    {
      std::cout << "cool" << me->getSpawnCoolDown() << std::endl;
      if (me->getSpawnCoolDown() == 0)
	{
	  pos = me->getPos();
	  me->spawnAllie(pos);
	  me->setSpawnCoolDown(me->getSpawnCoolDownBase());
	}
      else
	me->setSpawnCoolDown(me->getSpawnCoolDown() - 1);
    }

  bodys = world->getCollider().giveBodyInAreaCircle(actor->getPos().first, actor->getPos().second, 0, CHECK_DIST, 0);
  it1 = bodys.begin();
  savedPlayer = NULL;
  while (it1 != bodys.end())
    {
      if (((tmpPlayer = dynamic_cast<Player *>((*it1))) != NULL)
	  && (savedPlayer == NULL || Math::distBetween(tmpPlayer->getPos(), actor->getPos())
	      < Math::distBetween(savedPlayer->getPos(), actor->getPos())))
	savedPlayer = tmpPlayer;
      it1++;
    }
  if (savedPlayer == NULL)
    return;
  actor->changeOrientation(Math::getAngle(atan2(savedPlayer->getPos().second - actor->getPos().second,
						actor->getPos().first - savedPlayer->getPos().first)));
  idAttack = actor->spellBook.giveSpell(400, 30, true, NOAREA, 50, 10);
  
  double dist = world->getCollider().getDist(actor->getPos().first, actor->getPos().second,
					     *savedPlayer);
  if (actor->spellBook.spellNb(idAttack)->getRange() + actor->spellBook.spellNb(idAttack)->getRadius() > dist)
    {
      actor->castSpell(idAttack);
    }
  else
    {
      if (!actor->getMove())
	{
	  actor->setMove();
	}
    }
}
