//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ACTOR_HH
#define CPP_INDIE_STUDIO_ACTOR_HH

#include <string>
#include "Stats.hh"
#include "SpellContainer.hh"
#include "World.hh"

namespace gauntlet {
    class Actor {
    protected:
        std::string		name;
        int			id;
        Stats			stats;
        SpellContainer	spellBook;
        World			&world;
    };
};

#endif //CPP_INDIE_STUDIO_ACTOR_HH
