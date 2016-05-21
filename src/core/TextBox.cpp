#include "TextBox.hh"
#include "IUIObserver.hh"
#include "Core.hh"

gauntlet::core::TextBox::TextBox(Core & core, int idStart, Menu * parent,
				 std::string const & title) :
  Menu(core, idStart, parent)
{
  buttons.push_back(Control(TEXTBOX, title, NULL, PCENTER, idStart, core.ogre));
}

gauntlet::core::TextBox::~TextBox()
{ }

bool
gauntlet::core::TextBox::keyDown(Command cmd)
{
  if (!isOpen)
    return (false);

  IUIObserver::Key key = core.getLastKey();
  if (key == IUIObserver::KEY_BACK && text.length() > 0)
    text = text.substr(0, text.length() - 1);
  else if (key >= IUIObserver::KEY_A && key <= IUIObserver::KEY_Z)
    {
      char c = (text.length() == 0) ?
	((char)key - IUIObserver::KEY_A + 'A') : ((char)key - IUIObserver::KEY_A + 'a');
      text.append(1, c);
      buttons[0].setStr(text);
    }
  struct t_hitItem item;
  item.data = text;
  buttons[0].update(item);
  return (Menu::keyDown(cmd));
}
