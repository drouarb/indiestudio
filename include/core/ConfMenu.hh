//
// ConfMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Wed May 11 14:55:15 2016 Esteban Lewis
//

#ifndef  CONFMENU_HH_
# define CONFMENU_HH_

# include <map>
# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			ConfMenu : public Menu
    {
    public:
      ConfMenu(Core &, int idStart);
      ~ConfMenu();

      void			draw();
      void			undraw();
      bool			keyDown(Command);

    protected:
      std::map<int, void (ConfMenu::*)(Command)> funs;
      std::map<IUIObserver::Key, std::string> keyNames;
      bool			waitForKey;

      std::string const &	getKeyName(IUIObserver::Key);
      void			doButton(Command);

      void			doReturn(Command);
      void			doKeylink(Command);
    };
  };
};

#endif
