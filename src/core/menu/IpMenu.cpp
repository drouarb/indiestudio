#include "IpMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "ConnectMenu.hh"

gauntlet::core::IpMenu::IpMenu(Core & core, int idStart, Menu * parent) :
  TextBox(core, idStart, parent, "Server I.P.")
{
  buttons.push_back(Control(BUTTON, "OK", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
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
  static_cast<ConnectMenu *>(parent)->ip = text;
  setOpen(false);
}
