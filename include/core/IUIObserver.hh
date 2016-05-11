//
// EventHandler.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:52:22 2016 Esteban Lewis
// Last update Wed May 11 14:53:36 2016 Esteban Lewis
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
	  KEY_ESC,
          KEY_MOUSE1,
          KEY_MOUSE2,
          KEY_TAB,
          KEY_SPACE,
          KEY_BACK,
          KEY_A,
          KEY_B,
          KEY_C,
          KEY_D,
          KEY_E,
          KEY_F,
          KEY_G,
          KEY_H,
          KEY_I,
          KEY_J,
          KEY_K,
          KEY_L,
          KEY_M,
          KEY_N,
          KEY_O,
          KEY_P,
          KEY_Q,
          KEY_R,
          KEY_S,
          KEY_T,
          KEY_U,
          KEY_V,
          KEY_W,
          KEY_X,
          KEY_Y,
          KEY_Z
	};
    };
  };
};

#endif
