//
// GameObject.hh for GameObject in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio/include
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May  9 14:06:15 2016 Alexis Trouve
// Last update Sat May 14 15:00:56 2016 Alexis Trouve
//

#ifndef GAMEOBJECT_HH_
# define GAMEOBJECT_HH_

#include "ContainerObject.hh"
#include "ABody.hh"

namespace gauntlet
{

  class GameObject : public ContainerObject, public ABody
    {
    public:
      GameObject(bool collide, int nid, double posx,
		 double posy, double sizex, double sizey, short norient);
      GameObject(int nid, double posx, double posy, double sizex,
		 double sizey, short norient);
      ~GameObject();
    };
};

#endif
