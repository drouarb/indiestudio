#ifndef WORLD_HH_
# define WORLD_HH_

#include <string>
#include <list>
#include "ABody.hh"
#include "Collider.hh"
#include "BodyFactory.hh"
#include "BasicIA.hh"

namespace			gauntlet
{
  namespace			world
  {
    class			World
    {
    private:
      Collider			*collider;
      BodyFactory		*Factory;
      std::vector<BasicIA*>	IAs;
      std::list<ABody*>		bodys;
      double			sizeX;
      double			sizeY;
      //network::PacketFactory	packetFactory;
    public:
      World();
      ~World();

      void			update();
      void			loadGame(std::string const & file);
      void			initNetwork();
      void			gameLoop();
      void			tester();
      void			applyMoveActor();
      void			applyIA();
      void			notifyDeath(ABody *body);
      void			addNewBody(double xpos, double ypos, const std::string& name, short orientation);
      Collider&			getCollider();
    };
  };
};

#endif
