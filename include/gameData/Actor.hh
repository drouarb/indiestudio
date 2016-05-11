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
  class Actor : public ABody
  {
  protected:
    std::string			name;
    Stats			stats;
    //SpellContainer		spellBook;
    world::World		*world;
  public:
    Actor(bool collide, int nid, double posx,
	  double posy, double sizex, double sizey, short norient);
    Actor(int nid, double posx, double posy, double sizex,
	  double sizey, short norient);
    ~Actor();
  };
};

#endif //CPP_INDIE_STUDIO_ACTOR_HH
