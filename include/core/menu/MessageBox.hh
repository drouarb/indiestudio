#ifndef  MESSAGEBOX_HH_
# define MESSAGEBOX_HH_

# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			MessageBox : public Menu
    {
    public:
      MessageBox(Core &, int idStart, Menu * parent, std::string const &);
      ~MessageBox();

      void			draw();
      void			undraw();
      void			setMsg(std::string const &);

    protected:
      void			doButton(int, struct t_hitItem &);
    };
  };
};

#endif
