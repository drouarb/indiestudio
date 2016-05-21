#ifndef  CHARMENU_HH_
# define CHARMENU_HH_

# include "TextBox.hh"
# include "PlayerChars.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			CharMenu : public TextBox
    {
    public:
      CharMenu(Core &, int idStart, Menu * parent);
      ~CharMenu();

      void			draw();
      void			undraw();

    protected:
      std::map<int, void (CharMenu::*)(struct t_hitItem &)> funs;
      std::vector<std::string>	charTypes;
      world::PlayerChar		charType;

      void			doButton(int, struct t_hitItem &);

      void			doChartype(struct t_hitItem &);
      void			doOk(struct t_hitItem &);
    };
  };
};

#endif
