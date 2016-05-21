#include "ConnectMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "IpMenu.hh"

gauntlet::core::ConnectMenu::ConnectMenu(Core & core, int idStart, Menu * parent) :
  TextBox(core, idStart, parent, "Server port")
{
  ip = "";

  buttons.push_back(Control(CHECKBOX, "Local server", &serverTypes, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConnectMenu::*)(struct t_hitItem &)>
	      (buttons[buttons.size() - 1].getId(), &ConnectMenu::doLocal));

  buttons.push_back(Control(CHECKBOX, "Distant server", &serverTypes, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConnectMenu::*)(struct t_hitItem &)>
	      (buttons[buttons.size() - 1].getId(), &ConnectMenu::doDistant));

  buttons.push_back(Control(BUTTON, "Connect", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConnectMenu::*)(struct t_hitItem &)>
	      (buttons[buttons.size() - 1].getId(), &ConnectMenu::doConnect));

  buttons.push_back(Control(BUTTON, "Cancel", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConnectMenu::*)(struct t_hitItem &)>
	      (buttons[buttons.size() - 1].getId(), &ConnectMenu::doCancel));


  submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
  submenus.push_back(new IpMenu(core, idStart + MENU_ID_LAYER, this));
}

gauntlet::core::ConnectMenu::~ConnectMenu()
{ }

void
gauntlet::core::ConnectMenu::draw()
{
  drawButtons();

  struct t_hitItem item;
  item.type = CHECKBOX;
  item.state = CHECKED;
  if (ip == "127.0.0.1")
    {
      item.data = buttons[1].getStr();
      buttons[1].update(item);
    }
  else if (ip != "")
    {
      item.data = buttons[2].getStr();
      buttons[2].update(item);
    }
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

void
gauntlet::core::ConnectMenu::doLocal(struct t_hitItem & item)
{
  if (item.state == CHECKED)
    {
      struct t_hitItem other;
      other.type = CHECKBOX;
      other.data = buttons[2].getStr();
      other.state = NOCHECKED;
      buttons[2].update(other);

      ip = "127.0.0.1";
    }
}

void
gauntlet::core::ConnectMenu::doDistant(struct t_hitItem & item)
{
  if (item.state == CHECKED)
    {
      struct t_hitItem other;
      other.type = CHECKBOX;
      other.data = buttons[1].getStr();
      other.state = NOCHECKED;
      buttons[1].update(other);

      submenus[1]->setOpen(true);
    }
}

void
gauntlet::core::ConnectMenu::doConnect(struct t_hitItem & item)
{
  //try to convert port and ip
}

void
gauntlet::core::ConnectMenu::doCancel(struct t_hitItem & item)
{
  setOpen(false);
}
