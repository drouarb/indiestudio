//
// BasicAI.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:42:26 2016 Alexis Trouve
// Last update Tue May 24 12:07:19 2016 Alexis Trouve
//

#ifndef BASICAI_HH_
# define BASICAI_HH_

#include <string>
#include "AbstractAI.hh"

namespace gauntlet
{

  class	Actor;
  
  namespace world
  {

    class	World;

    class	BasicAI : public AbstractAI
    {
    public:
      BasicAI(World *nworld);
      ~BasicAI();
      virtual int			launchAI(std::pair<double, double> pos);
      virtual void			launchAI(gauntlet::Actor *actor);
    };
  };
};

#endif
