//
// BasicIA.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:42:26 2016 Alexis Trouve
// Last update Sun May 22 15:57:31 2016 Alexis Trouve
//

#ifndef BASICIA_HH_
# define BASICIA_HH_

#include <string>
#include "Actor.hh"

#define IA_LAUNCH_DIST 800.0
#define CHECK_DIST 1000.0

namespace gauntlet
{
  namespace world
  {

    class	World;

    class	BasicIA
    {
    private:
      std::vector<Actor*>		actors;
      World				*world;
      std::string			nameIA;
    public:
      BasicIA(World *nworld);
      ~BasicIA();
      bool			setNewIA(Actor *actor);
      void			suprActor(int id);
      int			launchIA(std::pair<double, double> pos);
      void			launchIA(Actor *actor);
      const std::string&	getName() const;
    };
  };
};

#endif
