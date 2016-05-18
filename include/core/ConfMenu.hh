//
// ConfMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Tue May 17 14:17:54 2016 Esteban Lewis
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
      ConfMenu(Core &, int idStart, Menu * parent);
      ~ConfMenu();

      void			draw();
      void			undraw();
      bool			keyDown(Command);

    protected:
      std::map<int, void (ConfMenu::*)(int)> funs;
      std::map<IUIObserver::Key, std::string> keyNames;
      Command			cmdToSet;

      std::string const &	getKeyName(IUIObserver::Key);
      IUIObserver::Key		getNameKey(std::string const &);
      void			doButton(int);

      void			doReturn(int);
      void			doKeylink(int);
    };
  };
};

#endif
