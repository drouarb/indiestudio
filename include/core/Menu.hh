//
// Menu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:23:51 2016 Esteban Lewis
// Last update Tue May 10 13:34:12 2016 Esteban Lewis
//

#ifndef  MENU_HH_
# define MENU_HH_

# include <vector>
# include "MenuButton.hh"
# include "IUIObserver.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			Menu
    {
    public:
      Menu(Core &, int id_start);
      virtual ~Menu();

      virtual void		draw() = 0;
      virtual void		undraw() = 0;
      bool			keyDown(IUIObserver::Key);
      void			setOpen(bool);
      bool			getOpen();

    protected:
      virtual void		doButton(IUIObserver::Key) = 0;
      void			moveCursor(int newPos);
      void			drawButtons();
      void			undrawButtons();

      int			idStart;
      Core &			core;
      bool			isOpen;
      int			cursor;
      std::vector<MenuButton>	buttons;
      std::vector<Menu *>	submenus;
    };
  };
};

#endif
