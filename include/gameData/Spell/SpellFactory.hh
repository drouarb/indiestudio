//
// SpellFactory.hh for indi in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 18:02:31 2016 Alexis Trouve
// Last update Tue May 10 17:36:14 2016 Alexis Trouve
//

#ifndef SPELLFACTORY_HH_
# define SPELLFACTORY_HH_

#include "ASpell.hh"
#include "World.hh"
#include "DistAttack.hh"
#include "HealAttack.hh"
#include "MeleeAttack.hh"
#include "SpellFactory.hh"
#include "TeleportSpell.hh"

namespace gauntlet
{
  
  enum		SpellEnum
    {
      MELEE_BARBARE,
      MELEE_VALKYRIE
    };

  class	SpellFactory
  {
  public:
    SpellFactory();
    ~SpellFactory();
    gauntlet::ASpell	*giveSpell(gauntlet::SpellEnum type);
  };
};

#endif
