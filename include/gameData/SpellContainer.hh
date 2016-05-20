//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELLCONTAINER_HH
# define CPP_INDIE_STUDIO_SPELLCONTAINER_HH

#include <vector>
#include "ASpell.hh"

namespace gauntlet
{
  
  class ASpell;
  
    class SpellContainer
    {
    public:
      SpellContainer();
      ~SpellContainer();
      std::vector<gauntlet::ASpell*> spellList;
    };
}


#endif //CPP_INDIE_STUDIO_SPELLCONTAINER_HH
