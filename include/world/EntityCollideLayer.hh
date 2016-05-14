//
// EntityCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 10 20:28:30 2016 Alexis Trouve
// Last update Sat May 14 16:08:53 2016 Esteban Lewis
//

#ifndef ENTITYCOLLIDELAYER_HH_
# define ENTITYCOLLIDELAYER_HH_

#include <list>
#include <vector>
#include <math.h>
#include "PhysicCollideLayer.hh"
#include "ABody.hh"
#include "Math.hh"

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

    typedef CollidingArea*		t_ca_line;

    class	EntityCollideLayer
    {
      //private:
    public:
      gauntlet::world::CollidingArea	**map;
      std::list<gauntlet::ABody*>	Entity;
      double				sizeX;
      double				sizeY;
      //private:
    public:
      void				setCollidingAreaData();
      void				suprMapId(int id, int posx, int posy);
    public:
      EntityCollideLayer(gauntlet::world::PhysicCollideLayer *physicLayer);
      ~EntityCollideLayer();
      bool				canMovePoint(double posx, double posy);
      bool				tryMoveId(int id, double posx, double posy);
      void				suprId(int id);
      double				getDist(double ref_x, double ref_y, ABody &target);
      int				getAngle(double refx, double refy, int refa, ABody & target);
      std::list<gauntlet::ABody*>	giveBodyInAreaCircle(double posx, double posy, double rayon);
      std::list<gauntlet::ABody*>	giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle);
      bool				setNewBody(gauntlet::ABody *newBody);
    };
  };
};

#endif
