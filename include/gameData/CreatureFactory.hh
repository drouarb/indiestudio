//
// CreatureFactory.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 18:36:12 2016 Alexis Trouve
// Last update Sat May 14 15:00:35 2016 Alexis Trouve
//

#ifndef CREATUREFACT_HH_
# define CREATUREFACT_HH_

#include <vector>
#include "FactoryData.hh"
#include "Creature.hh"

namespace gauntlet
{

  class Creature;
  class	CreatureFactory;
  
  struct	CreatureStruct
  {
    gauntlet::BodyEnum		type;
    gauntlet::Creature	*(gauntlet::CreatureFactory::*givePtr)(int id);
  };

  class	CreatureFactory
  {
  private:
    std::vector<CreatureStruct>	creatureTab;
  private:
    void				fillCreatureTab();

    gauntlet::Creature	*giveMomie(int id);
  public:
    CreatureFactory();
    ~CreatureFactory();
    gauntlet::Creature	*giveCreature(gauntlet::BodyEnum type, int id);
  };
};

#endif
