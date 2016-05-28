#include "IpMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "ConnectMenu.hh"

gauntlet::core::IpMenu::IpMenu(Core & core, int idStart, Menu * parent) :
  TextBox(core, idStart, parent, "Server I.P.")
{
  buttons.push_back(Control(BUTTON, "OK", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  buttons.push_back(Control(BUTTON, "Cancel", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));

  submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::IpMenu::~IpMenu()
{ }

void
gauntlet::core::IpMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::IpMenu::undraw()
{
  undrawButtons();
}

void
gauntlet::core::IpMenu::doButton(int btnId, struct t_hitItem & item)
{
  if (btnId == buttons[1].getId())
    {
      int dotCount = 0;
      for (unsigned int i = 0; i < text.length(); ++i)
	{
	  if (text[i] == '.')
	    dotCount++;
	}
      if (dotCount != 3)
	{
	  static_cast<MessageBox *>(submenus[0])->setMsg("Incorrect I.P. address.");
	  submenus[0]->setOpen(true);
	  return ;
	}
      
      static_cast<ConnectMenu *>(parent)->ip = text;
      setOpen(false);
      static_cast<ConnectMenu *>(parent)->setPort(port);
    }
  else if (btnId == buttons[2].getId())
    {
      static_cast<ConnectMenu *>(parent)->ip = "";
      setOpen(false);
      static_cast<ConnectMenu *>(parent)->setPort(port);
    }
}
