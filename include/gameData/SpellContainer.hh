//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELLCONTAINER_HH
# define CPP_INDIE_STUDIO_SPELLCONTAINER_HH

#include <vector>

namespace gauntlet
{
  class Spell;

    class SpellContainer
    {
    public:
      SpellContainer();
      ~SpellContainer();
      std::vector<gauntlet::Spell*> spellList;
      void  addSpell(int SpellEnum);
    };
};


#endif //CPP_INDIE_STUDIO_SPELLCONTAINER_HH
