//
// Created by jonas_e on 5/9/16.
//

#include "SpellContainer.hh"

using namespace gauntlet;

SpellContainer::SpellContainer()
{

}

SpellContainer::~SpellContainer()
{

}

void SpellContainer::addSpell(SpellFactory::SpellEnum spellEnum, Actor *caster)
{
    Spell* spell = SpellFactory::giveSpell(spellEnum);
    spell->setCaster(caster);
    this->spellList.push_back(spell);
}


