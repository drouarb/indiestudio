#include <stdexcept>
#include "ConnectMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "IpMenu.hh"
#include "PacketFactory.hh"

gauntlet::core::ConnectMenu::ConnectMenu(Core & core, int idStart, Menu * parent) :
  TextBox(core, idStart, parent, "Server port")
{
  init = false;

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

  init = true;
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
  init = false;
}

void
gauntlet::core::ConnectMenu::undraw()
{
  undrawButtons();
}

void
gauntlet::core::ConnectMenu::setPort(std::string port)
{
  struct t_hitItem item;
  item.data = port;
  text = port;
  buttons[0].update(item);
}

void
gauntlet::core::ConnectMenu::doButton(int btnId, struct t_hitItem & item)
{
  (this->*(funs[btnId]))(item);
}

void
gauntlet::core::ConnectMenu::doLocal(struct t_hitItem & item)
{
  if (!init && item.state == CHECKED)
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
  if (!init && item.state == CHECKED)
    {
      struct t_hitItem other;
      other.type = CHECKBOX;
      other.data = buttons[1].getStr();
      other.state = NOCHECKED;
      buttons[1].update(other);

      static_cast<IpMenu *>(submenus[1])->port = text;
      submenus[1]->setOpen(true);
    }
}

void
gauntlet::core::ConnectMenu::doConnect(struct t_hitItem & item)
{
  if (text == "")
    {
      static_cast<MessageBox *>(submenus[0])->setMsg("Please enter the port to connect to.");
      submenus[0]->setOpen(true);
      return ;
    }
  int port = atoi(text.c_str());
  if (port <= 0)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg("Invalid port.");
      submenus[0]->setOpen(true);
      return ;
    }

  if (ip == "")
    {
      static_cast<MessageBox *>(submenus[0])->setMsg
	("Please select a server to connect to.");
      submenus[0]->setOpen(true);
      return ;
    }

  try
    {
      core.packetf = new network::PacketFactory(ip, port);
      core.serverAddr = std::pair<std::string, int>(ip, port);
      setOpen(false);
    }
  catch (std::runtime_error e)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg
	("Connection to " + ip + " on port " + text + " failed: " + std::string(e.what()));
      submenus[0]->setOpen(true);
    }
}

void
gauntlet::core::ConnectMenu::doCancel(struct t_hitItem & item)
{
  setOpen(false);
}
