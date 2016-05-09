//
// EventHandler.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:52:22 2016 Esteban Lewis
// Last update Mon May  9 11:08:59 2016 Esteban Lewis
//

#ifndef  COREUIOBSERVER_HH_
# define COREUIOBSERVER_HH_

# include "IUIObserver.hh"

namespace				gauntlet
{
  namespace				core
  {
    class				CoreUIObserver : public IUIObserver
    {
    public:
      CoreUIObserver();
      ~CoreUIObserver();
    };
  };
};

#endif
