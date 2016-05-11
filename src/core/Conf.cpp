//
// Conf.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Tue May 10 14:57:42 2016 Esteban Lewis
// Last update Wed May 11 14:34:25 2016 Esteban Lewis
//

#include "Conf.hh"

gauntlet::core::Conf::Conf()
{
  map.insert(std::pair<Command, IUIObserver::Key>(UP, IUIObserver::KEY_UP));
  map.insert(std::pair<Command, IUIObserver::Key>(DOWN, IUIObserver::KEY_DOWN));
  map.insert(std::pair<Command, IUIObserver::Key>(LEFT, IUIObserver::KEY_LEFT));
  map.insert(std::pair<Command, IUIObserver::Key>(RIGHT, IUIObserver::KEY_RIGHT));
  map.insert(std::pair<Command, IUIObserver::Key>(ESC, IUIObserver::KEY_ESC));
  map.insert(std::pair<Command, IUIObserver::Key>(ENTER, IUIObserver::KEY_ENTER));
}

gauntlet::core::Conf::~Conf()
{ }

void
gauntlet::core::Conf::setKey(Command to_replace, IUIObserver::Key replace_by)
{
  IUIObserver::Key old;

  for (std::map<Command, IUIObserver::Key>::iterator it = map.begin(); it != map.end(); ++it)
    {
      if (it->first == to_replace)
	{
	  old = it->second;
	  it->second = replace_by;
	  break ;
	}
    }

  for (std::map<Command, IUIObserver::Key>::iterator it = map.begin(); it != map.end(); ++it)
    {
      if (it->first != to_replace && it->second == replace_by)
	{
	  it->second = old;
	  break ;
	}
    }
}

gauntlet::core::Command
gauntlet::core::Conf::getLinkedKey(IUIObserver::Key key)
{
  for (std::map<Command, IUIObserver::Key>::iterator it = map.begin(); it != map.end(); ++it)
    {
      if (it->second == key)
	{
	  return (it->first);
	}
    }
  return (NONE);
}
