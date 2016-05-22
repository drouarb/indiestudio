//
// BasicIA.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:46:42 2016 Alexis Trouve
// Last update Sun May 22 16:03:32 2016 Alexis Trouve
//

#include "BasicIA.hh"
#include "World.hh"

using namespace gauntlet;
using namespace world;

BasicIA::BasicIA(World *nworld)
{
  world = nworld;
  nameIA = "BasicIA";
}

BasicIA::~BasicIA()
{
}

bool		BasicIA::setNewIA(Actor *actor)
{
  unsigned int	i;

  i = 0;
  while (i < actors.size())
    {
      if (actors[i]->getId() == actor->getId())
	return (false);
      ++i;
    }
  actors.push_back(actor);
  return (true);
}

void		BasicIA::suprActor(int id)
{
  unsigned int	i;

  i = 0;
  while (i < actors.size())
    {
      if (actors[i]->getId() == id)
	{
	  actors.erase(actors.begin() + i);
	  return ;
	}
      ++i;
    }
}

int		BasicIA::launchIA(std::pair<double, double> pos)
{
  unsigned int	i;
  int		nbrPlayed;

  i = 0;
  nbrPlayed = 0;
  while (i < actors.size())
    {
      if (Math::distBetween(pos, actors[i]->getPos()) < IA_LAUNCH_DIST)
	{
	  launchIA(actors[i]);
	  nbrPlayed += 1;
	}
      ++i;
    }
}

void			BasicIA::launchIA(Actor *actor)
{
  std::list<ABody*>	bodys;
  std::list<ABody*>::iterator it1;
  Player			*savedPlayer;
  Player			*tmpPlayer;

  bodys = world->getCollider().giveBodyInAreaCircle(actor->getPos().first, actor->getPos().second, CHECK_DIST);
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
  world->getCollider().applyVectorToId(actor->getId(), actor->getOrientation(), actor->stats.speed);
  // faire l'attack de melee
}

const std::string&	BasicIA::getName() const
{
  return (nameIA);
}
