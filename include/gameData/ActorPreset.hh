//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ACTORPRESET_HH
#define CPP_INDIE_STUDIO_ACTORPRESET_HH

#include "Stats.hh"
#include "SpellContainer.hh"

namespace gauntlet
{
  class ActorPreset
  {
  public:
    Stats stats;
    SpellContainer spells;
  public:
    ActorPreset();
    ~ActorPreset();
  };
};

#endif //CPP_INDIE_STUDIO_ACTORPRESET_HH
