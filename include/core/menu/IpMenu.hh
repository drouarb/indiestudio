#ifndef  IPMENU_HH_
# define IPMENU_HH_

# include "TextBox.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			IpMenu : public TextBox
    {
    public:
      IpMenu(Core &, int idStart, Menu * parent);
      ~IpMenu();

      void			draw();
      void			undraw();

    protected:
      std::map<int, void (IpMenu::*)(struct t_hitItem &)> funs;

      void			doButton(int, struct t_hitItem &);
    };
  };
};

#endif
