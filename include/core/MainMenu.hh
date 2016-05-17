//
// MainMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Tue May 17 15:50:31 2016 Esteban Lewis
//

#ifndef  MAINMENU_HH_
# define MAINMENU_HH_

# include <map>
# include "SaveloadMenu.hh"
# include "Core.hh"

# define MENU_SL 0
# define MENU_CONFIG 1

namespace			gauntlet
{
  namespace			core
  {
    class			MainMenu : public Menu
    {
    public:
      MainMenu(Core &, int idStart, Menu * parent);
      ~MainMenu();

      void			draw();
      void			undraw();
      bool			keyDown(Command);

    protected:
      std::map<int, void (MainMenu::*)()> funs;

      void			doButton(int);

      void			doPlay();
      void			doSaveload();
      void			doSettings();
      void			doExit();
    };
  };
};

#endif
