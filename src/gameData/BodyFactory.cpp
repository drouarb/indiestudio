//
// BodyFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 16:50:32 2016 Alexis Trouve
// Last update Thu May 12 17:02:13 2016 Alexis Trouve
//

#include "BodyFactory.hh"

using namespace gauntlet;

BodyFactory::BodyFactory()
{

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

void			BodyFactory::fillBodyTab()
{
  bodyTab.push_back({BARBARE, &BodyFactory::giveBarbare});
  bodyTab.push_back({ELF, &BodyFactory::giveElf});
  bodyTab.push_back({MAGE, &BodyFactory::giveMage});
  bodyTab.push_back({VALKYRIE, &BodyFactory::giveValkyrie});
  bodyTab.push_back({BROKINGWALLVERTICAL, &BodyFactory::giveBrokingWallVertical});
  bodyTab.push_back({MOMIE, &BodyFactory::giveMomie});
}

ABody	*BodyFactory::giveBarbare()
{
  return (actorFactory.giveActor(BodyEnum::BARBARE, giveNextId()));
}

ABody	*BodyFactory::giveElf()
{
  return (actorFactory.giveActor(BodyEnum::ELF, giveNextId()));
}

ABody	*BodyFactory::giveMage()
{
  return (actorFactory.giveActor(BodyEnum::MAGE, giveNextId()));
}

ABody	*BodyFactory::giveValkyrie()
{
  return (actorFactory.giveActor(BodyEnum::VALKYRIE, giveNextId()));
}

ABody	*BodyFactory::giveBrokingWallVertical()
{
  return (gameObjectFactory.giveGameObject(BodyEnum::BROKINGWALLVERTICAL, giveNextId()));
}

ABody	*BodyFactory::giveMomie()
{
  return (actorFactory.giveActor(BodyEnum::MOMIE, giveNextId()));
}

ABody	*BodyFactory::giveBody(BodyEnum typeBody)
{
  unsigned int		i;

  i = 0;
  while (i < bodyTab.size())
    {
      if (bodyTab[i].bodyType == typeBody)
	return ((this->*bodyTab[i].givePtr)());
      ++i;
    }
}
