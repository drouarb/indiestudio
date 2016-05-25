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
      TextBox(Core &, int idStart, Menu * parent, std::string const & title);
      virtual ~TextBox();

      virtual bool		keyDown(Command);

      std::string const &	getText() const;
      void			setText(std::string const &);

    protected:
      std::string		text;
      std::string		caption;

      void			undrawButtons();
      void			drawButtons();
    };
  };
};

#endif
