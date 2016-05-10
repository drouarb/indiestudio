//
// SpellFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/src/gameData
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 18:00:14 2016 Alexis Trouve
// Last update Tue May 10 19:33:30 2016 Alexis Trouve
//

#include "SpellFactory.hh"

using namespace gauntlet;

SpellFactory::SpellFactory()
{
  fillSpellTab();
}

SpellFactory::~SpellFactory()
{

}

int		SpellFactory::giveNextId()
{
  static	int i = -1;

  ++i;
  return (i);
}

void		SpellFactory::fillSpellTab()
{
  spellTab.push_back({MELEE_BARBARE, &SpellFactory::giveMeleeBarbare});
  spellTab.push_back({MELEE_VALKYRIE, &SpellFactory::giveMeleeValkyrie});
  spellTab.push_back({DIST_BASIC_CAST_MAGE, &SpellFactory::giveDistBasicCastMage});
  spellTab.push_back({DIST_BASIC_ARROW_ELF, &SpellFactory::giveDistBasicArrowElf});
}

ASpell		*SpellFactory::giveMeleeBarbare()
{
  ASpell	*my;

  my = new MeleeAttack(false, 10, 50, 10.0, 3.0, giveNextId(), "Melee attack of the barbare //esteban", 0.3);
  return (my);
}

ASpell		*SpellFactory::giveMeleeValkyrie()
{
  ASpell	*my;

  my = new MeleeAttack(false, 15, 5, 18.0, 0.0, giveNextId(), "Melee attack of the valkyrie //esteban", 0.5);
  return (my);
}

ASpell		*SpellFactory::giveDistBasicCastMage()
{
  ASpell	*my;

  my = new DistAttack(false, 25, 0, 1, 120, 15.0, giveNextId(), "distance basic of the mage //esteban", 0.9);
  return (my);
}

ASpell		*SpellFactory::giveDistBasicArrowElf()
{
  ASpell	*my;

  my = new DistAttack(false, 10, 0, 1, 250.0, 1.0, giveNextId(), "distance basic attack of the elf //esteban", 0.3);
  return (my);
}


ASpell		*SpellFactory::giveSpell(SpellEnum type)
{
  unsigned int	i;

  i = 0;
  while (i < spellTab.size())
    {
      if (type == spellTab[i].spellEnum)
	return ((this->*spellTab[i].givePtr)());
      ++i;
    }
  return (NULL);
}
