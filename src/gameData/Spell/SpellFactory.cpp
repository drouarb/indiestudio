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
}

SpellFactory::~SpellFactory()
{

}

const std::map<SpellFactory::SpellEnum, SpellFactory::getSpell> gauntlet::SpellFactory::spellMap =
{
  {SpellFactory::VALKYRIA_ATTACK, &gauntlet::SpellFactory::getValkyriaAttack},
  {SpellFactory::VALKYRIA_DASH, &gauntlet::SpellFactory::getValkyriaDash},
  {SpellFactory::BARBARIAN_ATTACK, &gauntlet::SpellFactory::getBarbarianAttack},
  {SpellFactory::BARBARIAN_TORNADO, &gauntlet::SpellFactory::getBarbarianTornado},
        {SpellFactory::DRAUGR_ATTACK, &gauntlet::SpellFactory::getDraugrAttack}
};

int		SpellFactory::giveNextId()
{
  static	int i = -1;

  ++i;
  return (i);
}

Spell		*SpellFactory::giveSpell(SpellEnum type)
{
  return ((spellMap.at(type))());
}

gauntlet::Spell *SpellFactory::getValkyriaAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Valkyria Primary Attack", 100, 10, 10, Spell::Area::CIRCLE);
  return spell;
}

gauntlet::Spell *SpellFactory::getValkyriaDash() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Valkyria Dash", 100, 10, 10, Spell::Area::COLUMN);
  return spell;
}

gauntlet::Spell *SpellFactory::getBarbarianAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Barbarian Primary Attack", 100, 10, 10, Spell::Area::CONE);
  spell->setConeAngle(100);
  return spell;
}

gauntlet::Spell *SpellFactory::getBarbarianTornado() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Barbarian Tornado", 100, 10, 10, Spell::Area::CIRCLE);
  return spell;
}

gauntlet::Spell *SpellFactory::getDraugrAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Draugr Attack", 100, 10, 10, Spell::Area::CONE);
  spell->setConeAngle(40);
  return spell;
}

