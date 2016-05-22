//
// SpellFactory.hh for indi in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 18:02:31 2016 Alexis Trouve
// Last update Tue May 10 19:23:00 2016 Alexis Trouve
//

#ifndef SPELLFACTORY_HH_
# define SPELLFACTORY_HH_

#include <vector>
#include "ASpell.hh"
#include "World.hh"
#include "DistAttack.hh"
#include "HealAttack.hh"
#include "MeleeAttack.hh"
#include "SpellFactory.hh"
#include "TeleportSpell.hh"
#include <map>
#include <gameData/Spell/Spell.hh>

namespace gauntlet
{
  class SpellFactory;
  class	SpellFactory
  {
  public:
      SpellFactory();
      ~SpellFactory();
      typedef   gauntlet::Spell* (*getSpell)();
      enum		SpellEnum
      {
          VALKYRIA_ATTACK,
          VALKYRIA_DASH
      };
      const static std::map<SpellEnum , getSpell> spellMap;

  private:
    static int			        giveNextId();

  public:
      static Spell*              giveSpell(SpellEnum type);
      static Spell*              getValkyriaAttack();
      static Spell*              getValkyriaDash();
  };
};

#endif
