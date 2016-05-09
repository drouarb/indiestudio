//
// core.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:59:47 2016 Esteban Lewis
// Last update Mon May  9 11:19:30 2016 Esteban Lewis
//

#ifndef  CORE_HH_
# define CORE_HH_

# include "IUIObserver.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core
    {
    public:
      Core();
      ~Core();

      void			keyUp(IUIObserver::Key);
      void			keyDown(IUIObserver::Key);

    private:
      IUIObserver *		observer;
    };
  };
};

#endif
