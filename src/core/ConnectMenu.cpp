#include "ConnectMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"

gauntlet::core::ConnectMenu::ConnectMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::ConnectMenu::~ConnectMenu()
{ }

void
gauntlet::core::ConnectMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::ConnectMenu::undraw()
{
  undrawButtons();
}

void
gauntlet::core::ConnectMenu::doButton(int btnId, struct t_hitItem & item)
{
  (this->*(funs[btnId]))(item);
}
