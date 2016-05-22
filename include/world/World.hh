//
// World.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:55:06 2016 Esteban Lewis
// Last update Sun May 22 10:45:52 2016 Alexis Trouve
//

#ifndef WORLD_HH_
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
      double			sizeX;
      double			sizeY;
    public:
      World();
      ~World();

      void			update();
      void			loadGame(std::string file);
      void			initNetwork();
      void			gameLoop();
      void			tester();
      void			applyMoveActor();
      Collider&			getCollider();
    };
  };
};

#endif
