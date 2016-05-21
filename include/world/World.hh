#ifndef  WORLD_HH_
# define WORLD_HH_

#include <string>
#include <list>
#include "ABody.hh"
#include "Collider.hh"
#include "BodyFactory.hh"

namespace			gauntlet
{
  namespace			world
  {
    class			World
    {
    private:
      Collider			collider;
      BodyFactory		*Factory;
      std::list<ABody*>		bodys;
    public:
      World();
      ~World();

      void			update();
      void			loadGame(std::string file);
      void			tester();
      Collider&			getCollider();
    };
  };
};

#endif
