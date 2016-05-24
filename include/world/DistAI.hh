//
// DistAI.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Tue May 24 12:06:37 2016 Alexis Trouve
// Last update Tue May 24 12:22:03 2016 Alexis Trouve
//

#ifndef DISTAI_HH_
# define DISTAI_HH_

#define DIST_EVADE 300.0

#include "AbstractAI.hh"

namespace gauntlet
{
  class Actor;
  namespace world
  {
    class DistAI : AbstractAI
    {
    public:
      DistAI(World *nworld);
      ~DistAI();
      virtual int		launchAI(std::pair<double, double> pos);
      virtual void		launchAI(Actor *actor);
    };
  };
};

#endif
