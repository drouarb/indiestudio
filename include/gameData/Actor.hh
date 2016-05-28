//
// Created by jonas_e on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_ACTOR_HH
# define CPP_INDIE_STUDIO_ACTOR_HH

#include <string>
#include "ABody.hh"
#include "Stats.hh"
#include "SpellContainer.hh"

namespace gauntlet
{
  class SpellContainer;

  namespace world
  {
    class World;
  };

  class Actor : public ABody
  {
  public:
    Stats				stats;
    SpellContainer			spellBook;
    int					i;
    int					idAI;
    bool				ismoving = false;
  public:
    Actor(int nid, gauntlet::world::World *newWorld);
    ~Actor();
    virtual void			move();
    virtual bool			getMove() const;
    virtual void			setMove();
    virtual ABody			*clone(int id) const;
    void			addSpell(int spellEnum);

    void			setIdAI(int ia);
    int				getIdAI() const;
    void			castSpell(int spellEnum);
  };
};

#endif //CPP_INDIE_STUDIO_ACTOR_HH
