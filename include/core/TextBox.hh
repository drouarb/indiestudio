#ifndef  TEXTBOX_HH_
# define TEXTBOX_HH_

# include "Menu.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			TextBox : public Menu
    {
    public:
      TextBox(Core &, int idStart, Menu * parent);
      virtual ~TextBox();

      virtual bool		keyDown(Command);

    protected:
      std::string		text;
    };
  };
};

#endif
