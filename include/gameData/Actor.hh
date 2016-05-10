//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ACTOR_HH
#define CPP_INDIE_STUDIO_ACTOR_HH

#include <string>
#include "Stats.hh"
#include "SpellContainer.hh"
#include "World.hh"

namespace gauntlet
{
  class Actor
  {
  protected:
    std::pair<double, double>	coord;
    std::string			name;
    int				id;
    Stats			stats;
    //gauntlet::SpellContainer	spellBook;
    World			world;
  public:
    Actor();
    ~Actor();
  };
};

#endif //CPP_INDIE_STUDIO_ACTOR_HH
