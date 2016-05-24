//
// Created by jonas_e on 5/9/16.
//

#include "SpellContainer.hh"
#include "SpellFactory.hh"

using namespace gauntlet;

SpellContainer::SpellContainer()
{

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