#ifndef  LOBBY_HH_
# define LOBBY_HH_

# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Lobby : public Menu
    {
    public:
      Lobby(Core &, int idStart, Menu * parent);
      ~Lobby();

      void			draw();
      void			undraw();

    protected:
      std::map<int, void (Lobby::*)(struct t_hitItem &)> funs;
      int			connectLbl;

      void			doButton(int, struct t_hitItem &);

      void			doServer(struct t_hitItem &);
      void			doCharacter(struct t_hitItem &);
      void			doPlay(struct t_hitItem &);
    };
  };
};

#endif
