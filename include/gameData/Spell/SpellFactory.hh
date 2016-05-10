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

namespace gauntlet
{
  
  enum		SpellEnum
    {
      MELEE_BARBARE,
      MELEE_VALKYRIE,
      DIST_BASIC_CAST_MAGE,
      DIST_BASIC_ARROW_ELF
    };

  class SpellFactory;

  struct	giveSpellStruct
  {
    SpellEnum		spellEnum;
    gauntlet::ASpell	*(gauntlet::SpellFactory::*givePtr)();
  };
  
  class	SpellFactory
  {
  private:
    std::vector<giveSpellStruct>	spellTab;
  private:
    int			giveNextId();
    void		fillSpellTab();

    gauntlet::ASpell	*giveMeleeBarbare();
    gauntlet::ASpell	*giveMeleeValkyrie();
    gauntlet::ASpell	*giveDistBasicCastMage();
    gauntlet::ASpell	*giveDistBasicArrowElf();
  public:
    SpellFactory();
    ~SpellFactory();
    gauntlet::ASpell	*giveSpell(gauntlet::SpellEnum typeSpell);
  };
};

#endif
