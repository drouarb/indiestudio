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
#include <src/gameData/Spell/Spell.hh>

namespace gauntlet
{
  class SpellFactory;
  class	SpellFactory
  {
  public:
      typedef   gauntlet::Spell (gauntlet::SpellFactory::*getSpell)();
      enum		SpellEnum
      {
          VALKYRIA_ATTACK,
          VALKYRIA_DASH
      };
      static std::map<SpellEnum , getSpell > spellMap =
      {
              {VALKYRIA_ATTACK, &SpellFactory::getValkyriaAttack},
              {VALKYRIA_DASH, &SpellFactory::getValkyriaDash}
      };

  private:
    int			        giveNextId();
    Spell*              getValkyriaAttack();
    Spell*              getValkyriaDash();

  public:
    SpellFactory();
    ~SpellFactory();

      ASpell *giveSpell(SpellEnum type);
  };
};

#endif
