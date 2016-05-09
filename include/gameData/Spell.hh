//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_SPELL_HH
#define CPP_INDIE_STUDIO_SPELL_HH

#include <string>

namespace gauntlet
{
    class Spell
    {
    private:
      int id;
      std::string	name;
      int damage;
      double castTime;
      double range;
    public:
      Spell();
      ~Spell();
    };
};


#endif //CPP_INDIE_STUDIO_SPELL_HH
