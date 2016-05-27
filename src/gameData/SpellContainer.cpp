//
// Created by jonas_e on 5/9/16.
//

#include "SpellContainer.hh"
#include "SpellFactory.hh"
#include "AreaType.hh"

using namespace gauntlet;

SpellContainer::SpellContainer()
{
  Spell *spell;
}

SpellContainer::~SpellContainer()
{

}

void SpellContainer::addSpell(int spellEnum, Actor *caster)
{
    Spell* spell = SpellFactory::giveSpell(static_cast<SpellFactory::SpellEnum>(spellEnum));
    spell->setCaster(caster);
    this->spellList.push_back(spell);
}

Spell		*SpellContainer::giveSpell(double Range, double minRange, bool mustDamage,
					   Area Area, double Radius, short Angle)
{
  return (NULL);
}
