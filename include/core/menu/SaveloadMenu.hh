//
// MainMenu.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:06:35 2016 Esteban Lewis
// Last update Sat May 21 11:46:05 2016 Esteban Lewis
//

#ifndef  SAVELOADMENU_HH_
# define SAVELOADMENU_HH_

# define SAVE_DIR "./saves/"
# define NEW_SAVE "NEW_SAVE"

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
      std::map<int, void (SaveloadMenu::*)(struct t_hitItem &)> funs;
      std::vector<std::string>	saves;
      std::string		selected;

      void			getSaves();
      void			message(std::string const &);
      void			doButton(int, struct t_hitItem &);
      void			doSelect(struct t_hitItem &);
      void			doSave(struct t_hitItem &);
      void			doLoad(struct t_hitItem &);
      void			doReturn(struct t_hitItem &);
    };
  };
};

#endif
