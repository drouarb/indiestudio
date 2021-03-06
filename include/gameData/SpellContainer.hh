//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELLCONTAINER_HH
# define CPP_INDIE_STUDIO_SPELLCONTAINER_HH

#include <vector>
#include "AreaType.hh"

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

      int		giveSpell(double desireRange, double minRange, bool mustDamage,
				  Area desireArea, double desireRadius, short desireAngle);
      const Spell *	spellNb(int nb);
    };
};

#endif //CPP_INDIE_STUDIO_SPELLCONTAINER_HH
