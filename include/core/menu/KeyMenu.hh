//
// KeyMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Sun May 22 14:10:17 2016 Esteban Lewis
//

#ifndef  KEYMENU_HH_
# define KEYMENU_HH_

# include <map>
# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			KeyMenu : public Menu
    {
    public:
      KeyMenu(Core &, int idStart, Menu * parent);
      ~KeyMenu();

      void			draw();
      void			undraw();
      bool			keyDown(Command);

      void			setCmd(Command);

    protected:
      void			doButton(int, struct t_hitItem &);
      Command			cmdToSet;
    };
  };
};

#endif
