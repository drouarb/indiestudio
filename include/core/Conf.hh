//
// Conf.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Tue May 10 14:50:56 2016 Esteban Lewis
// Last update Tue May 10 15:46:01 2016 Esteban Lewis
//

#ifndef  CONF_HH_
# define CONF_HH_

# include <map>
# include "IUIObserver.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Conf
    {
    public:
      Conf();
      ~Conf();

      void			setKey(IUIObserver::Key to_replace,
				       IUIObserver::Key replace_by);
      IUIObserver::Key		getLinkedKey(IUIObserver::Key);

    private:
      std::map<IUIObserver::Key, IUIObserver::Key> map;
    };
  };
};

#endif
