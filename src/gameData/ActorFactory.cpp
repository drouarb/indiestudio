//
// ActorFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 19:05:59 2016 Alexis Trouve
// Last update Sat May 14 11:55:22 2016 Alexis Trouve
//

#include "ActorFactory.hh"

using namespace gauntlet;

ActorFactory::ActorFactory()
{
  fillActorTab();
}

ActorFactory::~ActorFactory()
{

}

void		ActorFactory::fillActorTab()
{
  actorTab.push_back({BARBARE, &ActorFactory::giveBarbare});
  actorTab.push_back({ELF, &ActorFactory::giveElf});
  actorTab.push_back({MAGE, &ActorFactory::giveMage});
  actorTab.push_back({VALKYRIE, &ActorFactory::giveValkyrie});
  actorTab.push_back({MOMIE, &ActorFactory::giveMomie});
}

Actor	*ActorFactory::giveBarbare(int id)
{
  return (playerFactory.givePlayer(BARBARE, id));
}

Actor	*ActorFactory::giveElf(int id)
{
  return (playerFactory.givePlayer(ELF, id));
}

Actor	*ActorFactory::giveMage(int id)
{
  return (playerFactory.givePlayer(MAGE, id));
}

Actor	*ActorFactory::giveValkyrie(int id)
{
  return (playerFactory.givePlayer(VALKYRIE, id));
}

Actor	*ActorFactory::giveMomie(int id)
{
  return (creatureFactory.giveCreature(MOMIE, id));
}

Actor	*ActorFactory::giveActor(BodyEnum type, int id)
{
  unsigned int		i;

  i = 0;
  while (i < actorTab.size())
    {
      if (actorTab[i].type == type)
	return ((this->*actorTab[i].givePtr)(id));
      ++i;
    }
  return (NULL);
}
