#ifndef  HUD_HH_
# define HUD_HH_

# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Hud : public Menu
    {
    public:
      Hud(Core &, int idStart, Menu * parent);
      ~Hud();

      void			draw();
      void			undraw();
      void			setStats(int);

    protected:
      void			doButton(int, struct t_hitItem &);
    };
  };
};

#endif
