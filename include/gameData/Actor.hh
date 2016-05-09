//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ACTOR_HH
#define CPP_INDIE_STUDIO_ACTOR_HH


class Actor {
private:
    Stats stats;
    SpellContainer spellBook;
    EntityActor &entity;
    World &world;
};


#endif //CPP_INDIE_STUDIO_ACTOR_HH
