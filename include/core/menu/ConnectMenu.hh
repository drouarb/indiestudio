#ifndef  CONNECTMENU_HH_
# define CONNECTMENU_HH_

# include "TextBox.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			ConnectMenu : public TextBox
    {
    public:
      ConnectMenu(Core &, int idStart, Menu * parent);
      ~ConnectMenu();

      void			draw();
      void			undraw();
      void			setPort(std::string port);

      std::string		ip;

    protected:
      std::map<int, void (ConnectMenu::*)(struct t_hitItem &)> funs;
      std::vector<std::string>	serverTypes;
      bool			init;

      void			doButton(int, struct t_hitItem &);

      void			doLocal(struct t_hitItem &);
      void			doDistant(struct t_hitItem &);
      void			doConnect(struct t_hitItem &);
      void			doCancel(struct t_hitItem &);
    };
  };
};

#endif
