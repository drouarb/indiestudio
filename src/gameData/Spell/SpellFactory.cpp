//
// SpellFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/src/gameData
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 18:00:14 2016 Alexis Trouve
// Last update Tue May 24 17:54:44 2016 Esteban Lewis
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
  {SpellFactory::WIZARD_FIREBALL, &gauntlet::SpellFactory::getWizardFireBall},
  {SpellFactory::WIZARD_FIRECONE, &gauntlet::SpellFactory::getWizardFireCone},
  {SpellFactory::RANGER_ATTACK, &gauntlet::SpellFactory::getRangerAttack},
  {SpellFactory::RANGER_EXPLOSIVE_ARROW, &gauntlet::SpellFactory::getRangerExplosiveArrow},
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

gauntlet::Spell *SpellFactory::getRangerAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Ranger Attack", 1500, 100, 50, Spell::Area::FLIGHT_PATH);
  return spell;
}

gauntlet::Spell *SpellFactory::getRangerExplosiveArrow() {
  Spell *spell = new Spell;
  spell->setBasicStats(giveNextId(), "Ranger Explosive Arrow", 1500, 100, 100, Spell::Area::CIRCLE);
  spell->setEffect(EffectName::CELLS, EffectName::ATOMIC);
  return spell;
}

gauntlet::Spell *SpellFactory::getWizardFireBall() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Wizard Fire Ball", 1500, 200, 50, Spell::Area::COLUMN);
  spell->setEffect(EffectName::PLASMA, EffectName::EXPLOSION);
  return spell;
}

gauntlet::Spell *SpellFactory::getWizardFireCone() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Wizard Fire Cone", 500, 100, 50, Spell::Area::CIRCLE);
  spell->setConeAngle(30);
  spell->setEffect(EffectName::PLASMA, EffectName::EXPLOSION);
  return spell;
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

