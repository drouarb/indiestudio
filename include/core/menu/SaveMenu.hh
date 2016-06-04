#ifndef  SAVEMENU_HH_
# define SAVEMENU_HH_

# define SAVE_DIR "./map/"
# define NEW_SAVE "NEW_MAP"

# include <map>
# include "TextBox.hh"
# include "Core.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			SaveMenu : public TextBox
    {
    public:
      SaveMenu(Core &, int idStart, Menu * parent);
      ~SaveMenu();

      void			draw();
      void			undraw();

    protected:
      std::map<int, void (SaveMenu::*)(struct t_hitItem &)> funs;

      void			doButton(int, struct t_hitItem &);
      void			doSave(struct t_hitItem &);
      void			doReturn(struct t_hitItem &);
    };
  };
};

#endif
