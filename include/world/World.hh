//
// World.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:55:06 2016 Esteban Lewis
// Last update Thu May 12 16:48:32 2016 Alexis Trouve
//

#ifndef  WORLD_HH_
# define WORLD_HH_

#include <string>
#include <list>
#include "ABody.hh"
#include "EntityCollideLayer.hh"
#include "PhysicCollideLayer.hh"

namespace			gauntlet
{
  namespace			world
  {
    class			World
    {
    private:
      std::list<gauntlet::ABody*>		bodys;
    public:
      World();
      ~World();

      void			update();
      void			loadGame(std::string file);
    };
  };
};

#endif
