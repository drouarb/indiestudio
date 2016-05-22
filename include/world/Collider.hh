//
// Collider.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 14:41:17 2016 Alexis Trouve
// Last update Fri May 20 14:42:51 2016 Alexis Trouve
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
      bool				tryMoveBody(int id, double pox, double posy);
      bool				applyVectorToId(int id, short orient, double speed);
      bool				setNewBody(ABody *body);
      void				suprBody(int id);
      std::list<gauntlet::ABody*>	giveBodyInAreaCircle(double posx, double posy, double radius);
      std::list<gauntlet::ABody*>	giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle);
    };
  };
};

#endif
