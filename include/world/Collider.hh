//
// Collider.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 14:41:17 2016 Alexis Trouve
// Last update Sat May 14 14:49:34 2016 Alexis Trouve
//

#ifndef COLLIDER_HH_
#define COLLIDER_HH_

#include <list>
#include "PhysicCollideLayer.hh"
#include "EntityCollideLayer.hh"
#include "ABody.hh"

namespace gauntlet
{
  namespace world
  {

    class	Collider
    {
    private:
      gauntlet::world::EntityCollideLayer	*dynamicLayer;
      gauntlet::world::PhysicCollideLayer	*physicLayer;
    public:
      Collider();
      ~Collider();
      bool		tryMoveBody(int id, double pox, double posy);
      bool		setNewBody(ABody *body);
      void		suprBody(int id);
    };
  };
};

#endif
