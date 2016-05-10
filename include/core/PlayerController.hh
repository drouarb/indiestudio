//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:49:54 2016 Esteban Lewis
// Last update Mon May  9 17:05:46 2016 Esteban Lewis
//

#ifndef  PLAYERCONTROLLER_HH_
# define PLAYERCONTROLLER_HH_

# include <map>
# include "IUIObserver.hh"

namespace				gauntlet
{
  namespace				core
  {
    class				PlayerController
    {
    public:
      PlayerController();
      ~PlayerController();

      enum				Action
	{
	  NONE,
	  ATTACK1,
	  ATTACK2,
	  ACTIVATE
	};

      void				doCmd(IUIObserver::Key, bool down);
      double				getMovementX();
      double				getMovementY();
      int				getAction();

      void				reset();
      void				loop();

    private:
      double				moveX;
      double				moveY;
      int				action;
      std::map<IUIObserver::Key, void (PlayerController::*)(bool)> ctrls;
      //Player				playerRef;

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
