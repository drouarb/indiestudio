//
// EntityCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 20:28:30 2016 Alexis Trouve
// Last update Sat May 14 14:48:15 2016 Alexis Trouve
//

#ifndef ENTITYCOLLIDELAYER_HH_
# define ENTITYCOLLIDELAYER_HH_

#include <list>
#include <vector>
#include "PhysicCollideLayer.hh"
#include "ABody.hh"

#define SIZE_CASE 400.0

namespace gauntlet
{
  namespace world
  {
    struct		CollidingArea
    {
      std::list<gauntlet::ABody*>	Entity;
      double		posx;
      double		posy;
      double		sizex;
      double		sizey;
    };

    class	EntityCollideLayer
    {
    private:
      gauntlet::world::CollidingArea	**map;
      std::list<gauntlet::ABody*>	Entity;
      unsigned int			sizeX;
      unsigned int			sizeY;
    private:
      void				setCollidingAreaData();
      void				suprMapId(int id, int posx, int posy);
    public:
      EntityCollideLayer(gauntlet::world::PhysicCollideLayer *physicLayer);
      ~EntityCollideLayer();
      bool				canMovePoint(double posx, double posy);
      bool				tryMoveId(int id, double posx, double posy);
      void				suprId(int id);
      bool				setNewBody(gauntlet::ABody *newBody);
      std::vector<gauntlet::ABody*>	giveBodyInAreaCircle(double posx, double posy, double rayon);
      std::vector<gauntlet::ABody*>	giveBodyInAreaCone(double posx, double posy, double size, short angle);
    };
  };
};

#endif
