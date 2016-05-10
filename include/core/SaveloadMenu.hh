//
// MainMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Tue May 10 13:34:44 2016 Esteban Lewis
//

#ifndef  SAVELOADMENU_HH_
# define SAVELOADMENU_HH_

# define SAVE_DIR "./saves/"

# include <map>
# include "Menu.hh"
# include "Core.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			SaveloadMenu : public Menu
    {
    public:
      SaveloadMenu(Core &, int idStart, Menu * parent);
      ~SaveloadMenu();

      void			draw();
      void			undraw();

    protected:
      std::map<int, void (SaveloadMenu::*)(IUIObserver::Key)> funs;
      MenuButton *		selected;
      Menu *			parent;

      void			getSaves();
      void			message(std::string const &);
      void			doButton(IUIObserver::Key);
      void			doSelect(IUIObserver::Key);
      void			doSave(IUIObserver::Key);
      void			doLoad(IUIObserver::Key);
      void			doReturn(IUIObserver::Key);
    };
  };
};

#endif
