//
// SpawnerAI.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:42:26 2016 Alexis Trouve
// Last update Sat Jun  4 17:28:57 2016 Alexis Trouve
//

#ifndef SPAWNERAI_HH_
# define SPAWNERAI_HH_

#include <string>
#include "AbstractAI.hh"

namespace gauntlet
{

  class	Actor;
  
  namespace world
  {

    class	World;

    class	SpawnerAI : public AbstractAI
    {
    public:
      SpawnerAI(World *nworld);
      ~SpawnerAI();
      virtual int			launchAI(std::pair<double, double> pos);
      virtual void			launchAI(gauntlet::Actor *actor);
    };
  };
};

#endif
