//
// ConfMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Tue May 10 15:36:12 2016 Esteban Lewis
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
      bool			keyDown(IUIObserver::Key);

    protected:
      std::map<int, void (ConfMenu::*)(IUIObserver::Key)> funs;
      bool			waitForKey;

      void			doButton(IUIObserver::Key);

      void			doReturn(IUIObserver::Key);
      void			doKeylink(IUIObserver::Key);
    };
  };
};

#endif
