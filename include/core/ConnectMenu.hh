#ifndef  CONNECTMENU_HH_
# define CONNECTMENU_HH_

# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			ConnectMenu : public Menu
    {
    public:
      ConnectMenu(Core &, int idStart, Menu * parent);
      ~ConnectMenu();

      void			draw();
      void			undraw();

    protected:
      std::map<int, void (ConnectMenu::*)(struct t_hitItem &)> funs;

      void			doButton(int, struct t_hitItem &);
    };
  };
};

#endif
