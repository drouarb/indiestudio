//
// AbstractAI.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 11:42:26 2016 Alexis Trouve
// Last update Sat Jun  4 13:56:00 2016 Alexis Trouve
//

#ifndef ABSTRACTAI_HH_
# define ABSTRACTAI_HH_

#include <string>
#include "Actor.hh"

#define AI_LAUNCH_DIST 1000.0
#define CHECK_DIST 1000.0


namespace gauntlet
{
  enum	EnumAI : int
    {
      NOAI = -1,
	MELEEBASICAI = 0,
	DISTBASICAI = 1
	};

  namespace world
  {

    class	World;

    class	AbstractAI
    {
    protected:
      std::vector<Actor*>		actors;
      World				*world;
      std::string			nameAI;
    public:
      AbstractAI(World *nworld);
      virtual ~AbstractAI();
      bool				setNewAI(gauntlet::Actor *actor);
      void				suprActor(int id);
      virtual int			launchAI(std::pair<double, double> pos) = 0;
      virtual void			launchAI(gauntlet::Actor *actor) = 0;
      const std::string&		getName() const;
    };
  };
};

#endif
