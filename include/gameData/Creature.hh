//
// Creature.hh for ls in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 15:34:16 2016 Alexis Trouve
// Last update Thu May 19 14:11:23 2016 Alexis Trouve
//

#ifndef CPP_INDIE_STUDIO_CREATURE_HH
# define CPP_INDIE_STUDIO_CREATURE_HH

#include "Actor.hh"

namespace gauntlet
{
  class Actor;

  class Creature : public Actor
  {
  public:
    Creature(int nid, gauntlet::world::World *newWorld);
    ~Creature();
  };
};

#endif //CPP_INDIE_STUDIO_CREATURE_HH
