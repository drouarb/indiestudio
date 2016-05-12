//
// BodyFactory.hh for BodyFactory in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 15:00:30 2016 Alexis Trouve
// Last update Thu May 12 17:01:34 2016 Alexis Trouve
//

#ifndef BODYFACTORY_HH_
# define BODYFACTORY_HH_

#include <vector>
#include "ActorFactory.hh"
#include "GameObjectFactory.hh"
#include "FactoryData.hh"
#include "ABody.hh"

namespace gauntlet
{
  class		BodyFactory;

  struct		giveBodyStruct
  {
    BodyEnum		bodyType;
    gauntlet::ABody	*(gauntlet::BodyFactory::*givePtr)();
  };

  class			BodyFactory
  {
  private:
    std::vector<giveBodyStruct>	bodyTab;
    gauntlet::ActorFactory	actorFactory;
    gauntlet::GameObjectFactory	gameObjectFactory;
  private:
    int			giveNextId();
    void		fillBodyTab();

    gauntlet::ABody	*giveBarbare();
    gauntlet::ABody	*giveValkyrie();
    gauntlet::ABody	*giveMage();
    gauntlet::ABody	*giveElf();
    gauntlet::ABody	*giveBrokingWallVertical();
    gauntlet::ABody	*giveMomie();
  public:
    BodyFactory();
    ~BodyFactory();
    gauntlet::ABody	*giveBody(gauntlet::BodyEnum typeBody);
  };
};

#endif
