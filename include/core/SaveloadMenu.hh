//
// MainMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Wed May 11 13:47:25 2016 Esteban Lewis
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
      std::map<int, void (SaveloadMenu::*)(Command)> funs;
      MenuButton *		selected;
      Menu *			parent;

      void			getSaves();
      void			message(std::string const &);
      void			doButton(Command);
      void			doSelect(Command);
      void			doSave(Command);
      void			doLoad(Command);
      void			doReturn(Command);
    };
  };
};

#endif
