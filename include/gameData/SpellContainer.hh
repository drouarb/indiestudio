//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELLCONTAINER_HH
# define CPP_INDIE_STUDIO_SPELLCONTAINER_HH

#include <vector>
#include "AreaType.hh"

#define SIZE_UNIT 20.0

namespace gauntlet
{
  class Spell;
  class Actor;

    class SpellContainer
    {
    public:
      std::vector<gauntlet::Spell*> spellList;
    public:
      SpellContainer();
      ~SpellContainer();
      void		addSpell(int spellEnum, gauntlet::Actor *caster);

      Spell		*giveSpell(double desireRange, double minRange, bool mustDamage,
				   Area desireArea, double desireRadius, short desireAngle);
    };
};

#endif //CPP_INDIE_STUDIO_SPELLCONTAINER_HH
