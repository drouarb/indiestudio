//
// Menu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:23:51 2016 Esteban Lewis
// Last update Wed May 11 13:46:41 2016 Esteban Lewis
//

#ifndef  MENU_HH_
# define MENU_HH_

# include <vector>
# include "MenuButton.hh"
# include "Conf.hh"

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
      virtual bool		keyDown(Command);
      void			setOpen(bool);
      bool			getOpen();

    protected:
      virtual void		doButton(Command) = 0;
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
