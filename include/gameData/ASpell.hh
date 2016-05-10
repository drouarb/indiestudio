//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELL_HH
#define CPP_INDIE_STUDIO_SPELL_HH

#include <string>
#include "World.hh"

namespace gauntlet
{
    class ASpell
    {
    private:
      int id;
      std::string	name;
      double castTime;
    public:
      ASpell(int nid, std::string nname, double ncastTime);
      ~ASpell();
      virtual void	 apply(double orientation, world::World &world) = 0;
    };
};


#endif //CPP_INDIE_STUDIO_SPELL_HH
