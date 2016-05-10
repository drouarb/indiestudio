//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELLCONTAINER_HH
#define CPP_INDIE_STUDIO_SPELLCONTAINER_HH

#include <list>
#include "ASpell.hh"

namespace gauntlet
{
  
  class ASpell;
  
    class SpellContainer
    {
      std::list<gauntlet::ASpell*> spellList;
    public:
      SpellContainer();
      ~SpellContainer();
    };
}


#endif //CPP_INDIE_STUDIO_SPELLCONTAINER_HH
