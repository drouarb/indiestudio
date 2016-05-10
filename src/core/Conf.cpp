//
// Conf.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Tue May 10 14:57:42 2016 Esteban Lewis
// Last update Tue May 10 15:47:20 2016 Esteban Lewis
//

#include "Conf.hh"

gauntlet::core::Conf::Conf()
{
  map.insert(std::pair<IUIObserver::Key, IUIObserver::Key>
	     (IUIObserver::KEY_UP, IUIObserver::KEY_UP));
  map.insert(std::pair<IUIObserver::Key, IUIObserver::Key>
	     (IUIObserver::KEY_DOWN, IUIObserver::KEY_DOWN));
  map.insert(std::pair<IUIObserver::Key, IUIObserver::Key>
	     (IUIObserver::KEY_LEFT, IUIObserver::KEY_LEFT));
  map.insert(std::pair<IUIObserver::Key, IUIObserver::Key>
	     (IUIObserver::KEY_RIGHT, IUIObserver::KEY_RIGHT));
  map.insert(std::pair<IUIObserver::Key, IUIObserver::Key>
	     (IUIObserver::KEY_ESC, IUIObserver::KEY_ESC));
  map.insert(std::pair<IUIObserver::Key, IUIObserver::Key>
	     (IUIObserver::KEY_ENTER, IUIObserver::KEY_ENTER));
}

gauntlet::core::Conf::~Conf()
{ }

void
gauntlet::core::Conf::setKey(IUIObserver::Key to_replace, IUIObserver::Key replace_by)
{
  IUIObserver::Key old;

  for (std::map<IUIObserver::Key, IUIObserver::Key>::iterator
	 it = map.begin(); it != map.end(); ++it)
    {
      if (it->first == to_replace)
	{
	  old = it->second;
	  it->second = replace_by;
	  break ;
	}
    }

  for (std::map<IUIObserver::Key, IUIObserver::Key>::iterator
	 it = map.begin(); it != map.end(); ++it)
    {
      if (it->first != to_replace && it->second == replace_by)
	{
	  it->second = old;
	  break ;
	}
    }
}

gauntlet::core::IUIObserver::Key
gauntlet::core::Conf::getLinkedKey(IUIObserver::Key key)
{
  for (std::map<IUIObserver::Key, IUIObserver::Key>::iterator
	 it = map.begin(); it != map.end(); ++it)
    {
      if (it->first == key)
	{
	  return (it->second);
	}
    }
  return (IUIObserver::KEY_NONE);
}
