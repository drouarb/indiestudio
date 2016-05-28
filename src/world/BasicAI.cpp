//
// BasicAI.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:46:42 2016 Alexis Trouve
// Last update Sun May 29 00:51:58 2016 Alexis Trouve
//

#include <iostream>
#include "BasicAI.hh"
#include "World.hh"

using namespace gauntlet;
using namespace world;

BasicAI::BasicAI(World *nworld) : AbstractAI(nworld)
{
  nameAI = "BasicAI";
}

BasicAI::~BasicAI()
{
}

int		BasicAI::launchAI(std::pair<double, double> pos)
{
  unsigned int	i;
  int		nbrPlayed;

  i = 0;
  nbrPlayed = 0;
  while (i < actors.size())
    {
      if (Math::distBetween(pos, actors[i]->getPos()) < AI_LAUNCH_DIST)
	{
	  launchAI(actors[i]);
	  nbrPlayed += 1;
	}
      ++i;
    }
  return (nbrPlayed);
}

void			BasicAI::launchAI(gauntlet::Actor *actor)
{
  std::list<ABody*>		bodys;
  std::list<ABody*>::iterator	it1;
  Player			*savedPlayer;
  Player			*tmpPlayer;
  int				idAttack;

  bodys = world->getCollider().giveBodyInAreaCircle(actor->getPos().first, actor->getPos().second, CHECK_DIST, 0, 0);
  it1 = bodys.begin();
  savedPlayer = NULL;
  while (it1 != bodys.end())
    {
      if (((tmpPlayer = dynamic_cast<Player*>((*it1))) != NULL)
	  && (savedPlayer == NULL || Math::distBetween(tmpPlayer->getPos(), actor->getPos())
	      < Math::distBetween(savedPlayer->getPos(), actor->getPos())))
	  savedPlayer = tmpPlayer;
      it1++;
    }
  if (savedPlayer == NULL)
    return ;
  actor->changeOrientation(Math::getAngle(-atan2(savedPlayer->getPos().first - actor->getPos().first,
						 savedPlayer->getPos().second - actor->getPos().second)));
  idAttack = actor->spellBook.giveSpell(30, 30, true, NOAREA, 0, 100);
  std::cout << "ia" << std::endl;
  actor->castSpell(idAttack);
}
