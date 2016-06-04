//
// Spawner.hh for spawn in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Fri Jun  3 21:52:09 2016 Alexis Trouve
// Last update Sat Jun  4 16:31:31 2016 Alexis Trouve
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
  protected:
    std::string			minionName;
    int				maxSpawn;
    std::list<Creature*>	myCrea;
    int				spawnCoolDown;
    int				spawnCoolDownBase;
  public:
    Spawner(int nid, gauntlet::world::World *newWorld);
    ~Spawner();
    void			spawnAllie(std::pair<double, double>& pos);
    int				getNbLinkedCreature() const;
    int				getMaxSpawn() const;
    void			setMaxSpawn(int nbr);
    const std::list<Creature*>&	getCreature() const;
    const std::string&		getMinionName() const;
    int				getSpawnCoolDown() const;
    int				getSpawnCoolDownBase() const;
    void			setSpawnCoolDown(int nbr);
    void			setSpawnCoolDownBase(int nbr);
  };
};

#endif
