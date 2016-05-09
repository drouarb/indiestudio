//
// EventHandler.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:52:22 2016 Esteban Lewis
// Last update Mon May  9 11:08:55 2016 Esteban Lewis
//

#ifndef  IUIOBSERVER_HH_
# define IUIOBSERVER_HH_

namespace				gauntlet
{
  namespace				core
  {
    class				IUIObserver
    {
    public:
      IUIObserver();
      ~IUIObserver();

      enum                              Key
	{
	  KEY_UP,
	  KEY_DOWN,
	  KEY_LEFT,
	  KEY_RIGHT,
	  KEY_ESC,
          KEY_ENTER
	};
    };
  };
};

#endif
