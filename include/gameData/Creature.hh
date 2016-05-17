//
// Creature.hh for ls in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 15:34:16 2016 Alexis Trouve
// Last update Sat May 14 15:21:34 2016 Alexis Trouve
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
    Creature(bool collide, int nid, double posx,
	     double posy, double sizex, double sizey, short norient);
    Creature(int nid, double posx, double posy, double sizex,
	     double sizey, short norient);
  };
};

#endif //CPP_INDIE_STUDIO_CREATURE_HH
