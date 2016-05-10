//
// EventHandler.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:52:22 2016 Esteban Lewis
// Last update Tue May 10 16:43:49 2016 Esteban Lewis
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
      virtual ~IUIObserver() { }

      enum                              Key
	{
	  KEY_NONE,
	  KEY_UP,
	  KEY_DOWN,
	  KEY_LEFT,
	  KEY_RIGHT,
          KEY_ENTER,
	  KEY_ESC
	};
    };
  };
};

#endif
