#include <stdexcept>
#include "ConnectMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "IpMenu.hh"
#include "PacketFactory.hh"
#include "SaveloadMenu.hh"
#include "PacketConnect.hh"
#include "PacketDisconnect.hh"
#include "PacketHandshake.hh"
#include "WaitPacket.hh"

gauntlet::core::ConnectMenu::ConnectMenu(Core & core, int idStart, Menu * parent) :
  TextBox(core, idStart, parent, "Server port")
{
  justConnected = false;
  init = false;
  portstr = "";
  local = false;

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
  submenus.push_back(new SaveloadMenu(core, idStart + MENU_ID_LAYER, this));
  submenus.push_back(new WaitPacket(core, idStart + MENU_ID_LAYER, this));
}

gauntlet::core::ConnectMenu::~ConnectMenu()
{ }

void
gauntlet::core::ConnectMenu::draw()
{
  if (justConnected)
    {
      justConnected = false;
      setOpen(false);
      return ;
    }

  drawButtons();

  if (portstr != "")
    {
      text = portstr;
      portstr = "";
      struct t_hitItem item;
      item.data = text;
      item.type = TEXTBOX;
      buttons[0].update(item);
    }

  init = true;
  struct t_hitItem item;
  item.type = CHECKBOX;
  item.state = CHECKED;
  if (local)
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


  if (static_cast<WaitPacket *>(submenus[3])->receivedValue())
    sendConnect();
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

      local = true;
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
      local = false;

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

  int port = -1;
  try
    {
      port = stoi(text);
    }
  catch (std::invalid_argument)
    { }
  if (port <= 0 || port > 65535)
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

  core.serverAddr = std::pair<std::string, int>(ip, port);
  if (local)
    {
      if (core.map == "")
	{
	  portstr = text;
	  submenus[2]->setOpen(true);
	  return ;
	}
      else
	{
	  core.createServer();
	}
    }

  try
    {
      if (core.packetf)
	core.disconnect("");
      core.packetf = new network::PacketFactory(ip, port);
      core.initPacketf();
      sendConnect();
      std::cout << "# connect end" << std::endl;
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

void
gauntlet::core::ConnectMenu::sendConnect()
{
  network::PacketConnect pc;
  bool recursive = static_cast<WaitPacket *>(submenus[3])->receivedValue();

  if (!recursive)
    core.networkmutex.lock();

  if (core.packetf == NULL)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg("Connection lost.");
      submenus[0]->setOpen(true);
      if (!recursive)
	core.networkmutex.unlock();
      return ;
    }

  if (static_cast<WaitPacket *>(submenus[3])->receivedValue() == false)
    {
      core.packetf->send((network::Packet&)pc);
      submenus[3]->setOpen(true);
    }
  else
    {
      network::PacketHandshake const * packet =
	dynamic_cast<network::PacketHandshake const *>
	(static_cast<WaitPacket *>(submenus[3])->getReceived());
      if (packet != NULL && packet->getConnectedPlayers() < packet->getMaxPlayers())
	{
	  static_cast<MessageBox *>(submenus[0])->setMsg("Connection succeeded.");
	  submenus[0]->setOpen(true);
	  justConnected = true;
	  setOpen(false);
	}
      else
	{
	  static_cast<MessageBox *>(submenus[0])->setMsg("No response from server.");
	  submenus[0]->setOpen(true);
	  core.disconnect("");
	}
    }

  if (!recursive)
    core.networkmutex.unlock();
}
