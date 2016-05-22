//
// Menu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:23:51 2016 Esteban Lewis
// Last update Sat May 21 13:41:22 2016 Esteban Lewis
//

#ifndef  MENU_HH_
# define MENU_HH_

# include <vector>
# include "Control.hh"
# include "Conf.hh"

# define MENU_ID_LAYER 100
# define MENU_ID_START 100

namespace			gauntlet
{
  namespace			core
  {
    class			Core;

    class			Menu
    {
    public:
      Menu(Core &, int id_start, Menu * parent);
      virtual ~Menu();

      virtual void		draw() = 0;
      virtual void		undraw() = 0;
      virtual bool		keyDown(Command);
      virtual bool		buttonClick(int buttonId, struct t_hitItem &);
      void			setOpen(bool);
      bool			getOpen();

    protected:
      virtual void		doButton(int id, struct t_hitItem &) = 0;
      void			drawButtons();
      void			undrawButtons();

      int			idStart;
      Core &			core;
      bool			isOpen;
      std::vector<Control>	buttons;
      std::vector<Menu *>	submenus;
      Menu *			parent;
    };
  };
};

#endif
