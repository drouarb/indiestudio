//
// Spawner.hh for spawn in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Fri Jun  3 21:52:09 2016 Alexis Trouve
// Last update Fri Jun  3 22:47:15 2016 Alexis Trouve
//

#ifndef CPP_INDIE_SPAWN
# define CPP_INDIE_SPAWN

#include <list>
#include "Creature.hh"
#include "Actor.hh"

namespace gauntlet
{
  class	Actor;

  class	Spawner : public Creature
  {
  private:
    std::string			name;
    int				maxSpawn;
    std::list<Creature*>	myCrea;
  public:
    Spawner(int nid, gauntlet::world::World *newWorld);
    ~Spawner();
    void		spawnAllie();
  };
};

#endif
