//
// SpellFactory.hh for indi in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 18:02:31 2016 Alexis Trouve
// Last update Tue May 24 15:06:29 2016 Alexis Trouve
//

#ifndef SPELLFACTORY_HH_
# define SPELLFACTORY_HH_

#include <vector>
#include "World.hh"
#include "DistAttack.hh"
#include "HealAttack.hh"
#include "MeleeAttack.hh"
#include "SpellFactory.hh"
#include "TeleportSpell.hh"
#include "Spell.hh"
#include <map>

namespace gauntlet
{
  class SpellFactory; //àvirer?
  class	SpellFactory
  {
  public:
      SpellFactory();
      ~SpellFactory();
      typedef   gauntlet::Spell* (*getSpell)();
      enum		SpellEnum
      {
          VALKYRIA_ATTACK,
          VALKYRIA_DASH,
          VALKYRIA_HEAL,
          BARBARIAN_ATTACK,
          BARBARIAN_TORNADO,
          WIZARD_FIREBALL,
          WIZARD_FIRECONE,
          RANGER_ATTACK,
          RANGER_EXPLOSIVE_ARROW,
          SIMPLE_ATTACK,
          ICEBALL
      };

      const static std::map<SpellEnum , getSpell> spellMap;

  private:
    static int			        giveNextId();

  public:
      static Spell*              giveSpell(SpellEnum type);
      static Spell*              getValkyriaAttack();
      static Spell*              getValkyriaDash();
      static Spell*              getBarbarianAttack();
      static Spell*              getBarbarianTornado();
      static Spell*              getWizardFireBall();
      static Spell*              getWizardFireCone();
      static Spell*              getRangerAttack();
      static Spell*              getRangerExplosiveArrow();

      static Spell*              simpleAttack();
      static Spell*              iceBall();

      static Spell*              getValkyriaHeal();
  };
};

#endif
