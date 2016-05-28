//
// SpellFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/src/gameData
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 18:00:14 2016 Alexis Trouve
// Last update Fri May 27 23:35:10 2016 Alexis Trouve
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
  {SpellFactory::ICEBALL, &gauntlet::SpellFactory::iceBall},
  {SpellFactory::SIMPLE_ATTACK, &gauntlet::SpellFactory::simpleAttack}
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

  spell->setBasicStats(giveNextId(), "Ranger Attack", 1500, 100, 50, Area::FLIGHT_PATH, SoundName::BOW);
  return spell;
}

gauntlet::Spell *SpellFactory::getRangerExplosiveArrow() {
  Spell *spell = new Spell;
  spell->setBasicStats(giveNextId(), "Ranger Explosive Arrow", 1500, 100, 100, Area::CIRCLE, SoundName::MAGIC_EXPLOSION_1);
  spell->setEffect(EffectName::CELLS, EffectName::ATOMIC);
  return spell;
}

gauntlet::Spell *SpellFactory::getWizardFireBall() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Wizard Fire Ball", 1500, 200, 50, Area::COLUMN, SoundName::MAGIC_EXPLOSION_2);
  spell->setEffect(EffectName::PLASMA, EffectName::EXPLOSION);
  return spell;
}

gauntlet::Spell *SpellFactory::getWizardFireCone() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Wizard Fire Cone", 500, 100, 50, Area::CIRCLE, SoundName::FIRE_BIG);
  spell->setConeAngle(80);
  spell->setEffect(EffectName::PLASMA, EffectName::EXPLOSION);
  return spell;
}

gauntlet::Spell *SpellFactory::getValkyriaAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Valkyria Primary Attack", 100, 10, 10, Area::CIRCLE, SoundName::SWORD_HIT);
  return spell;
}

gauntlet::Spell *SpellFactory::getValkyriaDash() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Valkyria Dash", 100, 10, 10, Area::COLUMN, SoundName::SPIKE_TRAP_2);
  return spell;
}

gauntlet::Spell *SpellFactory::getBarbarianAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Barbarian Primary Attack", 100, 10, 10, Area::CONE, SoundName::HAMMER_HIT_SOFT);
  spell->setConeAngle(200);
  return spell;
}

gauntlet::Spell *SpellFactory::getBarbarianTornado() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Barbarian Tornado", 100, 10, 10, Area::CIRCLE, SoundName::MAGIC_BATTLECRY);
  return spell;
}

gauntlet::Spell *SpellFactory::iceBall() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Ice Ball", 1500, 200, 50, Area::COLUMN, SoundName::MAGIC_EXPLOSION_2);
  spell->setEffect(EffectName::SNOW, EffectName::BLIND);
  return spell;
}

gauntlet::Spell *SpellFactory::simpleAttack() {
  Spell *spell = new Spell;

  spell->setBasicStats(giveNextId(), "Simple Attack", 100, 10, 10, Area::CONE, SoundName::AXE_HIT_SOFT);
  spell->setConeAngle(60);
  return spell;
}

