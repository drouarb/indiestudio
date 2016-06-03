//
// EntityCollideLayer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 25 18:33:15 2016 Alexis Trouve
// Last update Fri Jun  3 22:22:15 2016 Alexis Trouve
//

#ifndef ENTITYCOLLIDELAYER_HH_
# define ENTITYCOLLIDELAYER_HH_

#include <list>
#include <vector>
#include <math.h>
#include <mutex>
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
    private:
      gauntlet::world::CollidingArea	**map;
      std::list<gauntlet::ABody*>	Entity;
      unsigned int			sizeX;
      unsigned int			sizeY;
      std::mutex			mutex;
    private:
      void				setCollidingAreaData();
      void				suprMapId(int id, int posx, int posy);
    private:
      bool				bodyLineIntersection(double refx, double refy,
							     short angle, double bodySizeX,
							     double bodySizeY, ABody & body);
    public:
      EntityCollideLayer(gauntlet::world::PhysicCollideLayer *physicLayer);
      ~EntityCollideLayer();

      void				forceMoveId(int id, double posx, double posy);
      bool				tryMoveId(int id, double posx, double posy);
      void				applyVectorToId(int id, short orient, double speed);
      void				suprId(int id);
      std::list<gauntlet::ABody*>	getCollideBody();
      bool				setNewBody(gauntlet::ABody *newBody);
      void				forceSetBody(gauntlet::ABody *newBody);
      double				getDist(double ref_x, double ref_y, const ABody &target);
      int				getAngle(double refx, double refy, int refa, const ABody &target);
      std::list<gauntlet::ABody*>	giveBodyInAreaCircle(double posx, double posy, double rayon);
      std::list<gauntlet::ABody*>	giveBodyInAreaCone(double posx, double posy, short ref_angle, double size, short cone_angle);
      gauntlet::ABody			*getBodyId(int id);

        std::list<ABody *> giveBodyInAreaRectangle(double posx, double posy, short ratio, double size, short unused);
    };
  };
};

#endif
