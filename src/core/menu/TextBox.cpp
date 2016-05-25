#include "TextBox.hh"
#include "IUIObserver.hh"
#include "Core.hh"

gauntlet::core::TextBox::TextBox(Core & core, int idStart, Menu * parent,
				 std::string const & title) :
  Menu(core, idStart, parent)
{
  textSet = false;
  caption = title;
  buttons.push_back(Control(TEXTBOX, title, NULL, PCENTER, idStart, core.ogre));
}

gauntlet::core::TextBox::~TextBox()
{ }

bool
gauntlet::core::TextBox::keyDown(Command cmd)
{
  if (!isOpen)
    return (false);
  if (openSubMenu())
    return (Menu::keyDown(cmd));

  IUIObserver::Key key = core.getLastKey();
  if (key == IUIObserver::KEY_BACK && text.length() > 0)
    {
      if (textSet)
	text = "";
      else
	text = text.substr(0, text.length() - 1);
    }
  else if (key >= IUIObserver::KEY_A && key <= IUIObserver::KEY_Z)
    {
      char c = (text.length() == 0) ?
	((char)key - IUIObserver::KEY_A + 'A') : ((char)key - IUIObserver::KEY_A + 'a');
      text.append(1, c);
    }
  else if (key >= IUIObserver::KEY_0 && key <= IUIObserver::KEY_9)
    {
      char c = key - IUIObserver::KEY_0 + '0';
      text.append(1, c);
    }
  else if (key == IUIObserver::KEY_PERIOD)
    text += ".";

  textSet = false;

  struct t_hitItem item;
  item.data = text;
  buttons[0].update(item);
  return (Menu::keyDown(cmd));
}

std::string const &
gauntlet::core::TextBox::getText() const
{
  return (text);
}

void
gauntlet::core::TextBox::setText(std::string const & newtext)
{
  textSet = true;
  text = newtext;
}

void
gauntlet::core::TextBox::drawButtons()
{
  Menu::drawButtons();
  
  struct t_hitItem item;
  item.data = text;
  buttons[0].update(item);
}

void
gauntlet::core::TextBox::undrawButtons()
{
  Menu::undrawButtons();
  buttons[0].setStr(caption);
  text = "";
  textSet = false;
}
