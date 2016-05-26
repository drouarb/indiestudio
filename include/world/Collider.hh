//
// Collider.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 14:41:17 2016 Alexis Trouve
// Last update Thu May 26 13:19:22 2016 Alexis Trouve
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
      unsigned int				sizeX;
      unsigned int				sizeY;
    public:
      Collider(unsigned int xsize, unsigned int ysize);
      ~Collider();
      bool				tryMoveBody(int id, double pox, double posy);
      bool				applyVectorToId(int id, short orient, double speed);
      bool				setNewBody(ABody *body);
      bool				setNewBodyNoCheckEntity(ABody *body);
      void				suprBody(int id);
      std::pair<unsigned int, unsigned int>		getSizeMap() const;

      std::list<ABody *> giveBodyInAreaCircle(double posx, double posy, short unused, double radius, short unused2);
      std::list<ABody*>	giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle);
    };
  };
};

#endif
