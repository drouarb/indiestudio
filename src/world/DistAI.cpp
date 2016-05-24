//
// DistAI.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 24 12:09:30 2016 Alexis Trouve
// Last update Tue May 24 12:32:36 2016 Alexis Trouve
//

#include "DistAI.hh"
#include "World.hh"

using namespace gauntlet;
using namespace world;

DistAI::DistAI(World *nworld) : AbstractAI(nworld)
{
  nameAI = "DistAI";
}

DistAI::~DistAI()
{
}

int		DistAI::launchAI(std::pair<double, double> pos)
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

void		DistAI::launchAI(gauntlet::Actor *actor)
{
  std::list<ABody*>		bodys;
  std::list<ABody*>::iterator	it1;
  Player			*savedPlayer;
  Player			*tmpPlayer;
  short				ttRad;
  double			smallestDist;
  int				nbrPlayer;

  bodys = world->getCollider().giveBodyInAreaCircle(actor->getPos().first,
						    actor->getPos().second, CHECK_DIST, 0, 0);
  it1 = bodys.begin();
  savedPlayer = NULL;
  ttRad = 0;
  smallestDist = 10000000.0;
  nbrPlayer = 0;
  while (it1 != bodys.end())
    {
      if ((tmpPlayer = dynamic_cast<Player*>((*it1))) != NULL)
	{
          if (savedPlayer == NULL || Math::distBetween(tmpPlayer->getPos(), actor->getPos())
              < Math::distBetween(savedPlayer->getPos(), actor->getPos()))
	    {
	      smallestDist = Math::distBetween(tmpPlayer->getPos(), actor->getPos());
	      savedPlayer = tmpPlayer;
	    }
	  ttRad += Math::getAngle(atan2(tmpPlayer->getPos().first - actor->getPos().first,
					 tmpPlayer->getPos().second - actor->getPos().second));
	  nbrPlayer++;
	}
      it1++;
    }
  if (savedPlayer == NULL)
    return ;
  if (smallestDist <= DIST_EVADE)
    {
      actor->changeOrientation(Math::getAngle(ttRad / nbrPlayer));
    }
  else
    actor->changeOrientation(Math::getAngle(atan2(savedPlayer->getPos().first - actor->getPos().first,
						  savedPlayer->getPos().second - actor->getPos().second)));
}
