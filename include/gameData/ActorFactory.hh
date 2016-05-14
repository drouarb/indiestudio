//
// ActorFactory.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 18:36:12 2016 Alexis Trouve
// Last update Sat May 14 15:01:32 2016 Alexis Trouve
//

#ifndef ACTORFACT_HH_
# define ACTORFACT_HH_

#include <vector>
#include "PlayerFactory.hh"
#include "CreatureFactory.hh"
#include "Actor.hh"
#include "FactoryData.hh"

namespace gauntlet
{

  class Actor;
  class	ActorFactory;
  
  struct	ActorStruct
  {
    gauntlet::BodyEnum		type;
    gauntlet::Actor	*(gauntlet::ActorFactory::*givePtr)(int id);
  };

  class	ActorFactory
  {
  private:
    std::vector<ActorStruct>	actorTab;
    gauntlet::PlayerFactory	playerFactory;
    gauntlet::CreatureFactory	creatureFactory;
  private:
    void				fillActorTab();

    gauntlet::Actor		*giveBarbare(int id);
    gauntlet::Actor		*giveElf(int id);
    gauntlet::Actor		*giveMage(int id);
    gauntlet::Actor		*giveValkyrie(int id);
    gauntlet::Actor		*giveMomie(int id);
  public:
    ActorFactory();
    ~ActorFactory();
    gauntlet::Actor	*giveActor(gauntlet::BodyEnum type, int id);
  };
};

#endif
