//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:49:54 2016 Esteban Lewis
// Last update Tue May 24 16:13:28 2016 Esteban Lewis
//

#ifndef  PLAYERCONTROLLER_HH_
# define PLAYERCONTROLLER_HH_

# include <map>
# include "Conf.hh"
# include "PlayerChars.hh"

namespace				gauntlet
{
  namespace				core
  {
    class				PlayerController
    {
    public:
      PlayerController(std::string const & name, world::PlayerChar);
      ~PlayerController();

      enum				Action : int
	{
	  NONE = 0,
	  ATTACK1 = 1,
	  ATTACK2 = 2,
	  ACTIVATE = 3
	};

      std::string const &		getName() const;
      world::PlayerChar			getChar() const;
      void				doCmd(Command, bool down);
      std::pair<double, double>		getMovement();
      int				getAction();
      void				setAngle(short);

      void				loop();

      int				id;

    private:
      double				moveX;
      double				moveY;
      int				action;
      std::map<Command, void (PlayerController::*)(bool)> ctrls;
      void *				playerRef;
      world::PlayerChar			chartype;
      std::string			name;

      void				cmdUp(bool);
      void				cmdDown(bool);
      void				cmdLeft(bool);
      void				cmdRight(bool);
      void				cmdAttack1(bool);
      void				cmdAttack2(bool);
      void				cmdActivate(bool);
    };
  };
};

#endif
