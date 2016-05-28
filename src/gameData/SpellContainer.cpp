//
// Created by jonas_e on 5/9/16.
//

#include "Math.hh"
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

int		SpellContainer::giveSpell(double Range, double minRange, bool mustDamage,
					   Area Area, double Radius, short Angle)
{
  std::vector<double>	weightTab;
  unsigned int		highterI;
  Spell			*spell;
  unsigned int		i;

  if (spellList.size() == 0)
    return (-1);
  i = -1;
  while (++i < spellList.size())
    weightTab.push_back(1000.0);
  i = 0;
  while (i < weightTab.size())
    {
      spell = spellList[i];
      weightTab[i] += -world::Math::abs((Range - spell->getRange()) * 2.0);
      weightTab[i] += (minRange > spell->getRange()) ? 0.0 : -1000.0;
      weightTab[i] += (2.0 * spell->getDamage());
      if (Area != NOAREA)
	weightTab[i] += (Area == spell->getAreaType()) ? 300.0 : -1000.0;
      weightTab[i] += -((Radius - spell->getRange()) * 3.0);
      weightTab[i] += -((Angle - spell->getAngle()) * 4.0);
      ++i;
    }
  highterI = 0;
  i = 1;
  while (i < weightTab.size())
    {
      if (weightTab[i] > weightTab[highterI])
	highterI = i;
      ++i;
    }
  return (highterI);
}
