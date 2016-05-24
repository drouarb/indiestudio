//
// World.hh for World in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:51:22 2016 Alexis Trouve
// Last update Mon May 23 21:14:13 2016 Alexis Trouve
//

#ifndef WORLD_HH_
# define WORLD_HH_

#include <string>
#include <list>
#include "ABody.hh"
#include "Collider.hh"
#include "BodyFactory.hh"
#include "BasicIA.hh"
#include "GameServer.hh"

namespace			gauntlet
{
  namespace			world
  {
    class			GameServer;
    
    class			World
    {
    private:
      Collider			*collider;
      BodyFactory		*Factory;
      std::vector<BasicIA*>	IAs;
      std::list<ABody*>		bodys;
      double			sizeX;
      double			sizeY;
      std::pair<double, double>	spawnPoint;
      GameServer		*gameServer;
      //network::PacketFactory	packetFactory;
    public:
      World(GameServer *ngameServer);
      ~World();

      void			update();
      void			loadGame(std::string const & file);
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
