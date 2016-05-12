//
// EntityCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 20:28:30 2016 Alexis Trouve
// Last update Thu May 12 16:26:39 2016 Alexis Trouve
//

#ifndef ENTITYCOLLIDELAYER_HH_
# define ENTITYCOLLIDELAYER_HH_

#include <list>
#include "PhysicCollideLayer.hh"
#include "ABody.hh"

#define SIZE_CASE 400.0

namespace gauntlet
{
  namespace world
  {
    struct		CollidingArea
    {
      std::list<ABody*>	Entity;
      double		posx;
      double		posy;
      double		sizex;
      double		sizey;
    };

    class	EntityCollideLayer
    {
    private:
      gauntlet::world::CollidingArea	**Map;
    public:
      EntityCollideLayer(gauntlet::world::PhysicCollideLayer *physicLayer);
      ~EntityCollideLayer();
    };
  };
};

#endif
