//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ACTOR_HH
#define CPP_INDIE_STUDIO_ACTOR_HH

#include <string>

class Actor
{
private:
  std::pair<double, double>	coord;
  std::string			name;
  int				id;
  Stats				stats;
  SpellContainer		spellBook;
  World				&world;
public:
  Actor();
  ~Actor();
};


#endif //CPP_INDIE_STUDIO_ACTOR_HH
