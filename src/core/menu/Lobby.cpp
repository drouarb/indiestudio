#include <sstream>
#include "Lobby.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "CharMenu.hh"
#include "ConnectMenu.hh"
#include "PacketSelectPlayer.hh"
#include "PacketStartGame.hh"
#include "WaitPacket.hh"
#include "PlayerController.hh"

gauntlet::core::Lobby::Lobby(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  buttons.push_back(Control(LABEL, "", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  buttons.push_back(Control(BUTTON, "Connect to server", NULL, PCENTER,
  			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (Lobby::*)(struct t_hitItem &)>
  	      (buttons[buttons.size() - 1].getId(), &Lobby::doServer));

  buttons.push_back(Control(LABEL, "", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  buttons.push_back(Control(BUTTON, "Create character", NULL, PCENTER,
  			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (Lobby::*)(struct t_hitItem &)>
  	      (buttons[buttons.size() - 1].getId(), &Lobby::doCharacter));

  buttons.push_back(Control(BUTTON, "- Play -", NULL, PCENTER,
  			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (Lobby::*)(struct t_hitItem &)>
  	      (buttons[buttons.size() - 1].getId(), &Lobby::doPlay));

  buttons.push_back(Control(BUTTON, "Cancel", NULL, PCENTER,
  			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (Lobby::*)(struct t_hitItem &)>
  	      (buttons[buttons.size() - 1].getId(), &Lobby::doCancel));

  submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
  submenus.push_back(new CharMenu(core, idStart + MENU_ID_LAYER, this));
  submenus.push_back(new ConnectMenu(core, idStart + MENU_ID_LAYER, this));
  submenus.push_back(new WaitPacket(core, idStart + MENU_ID_LAYER, this));
}

gauntlet::core::Lobby::~Lobby()
{ }

void
gauntlet::core::Lobby::draw()
{
  if (core.packetf == NULL)
    buttons[0].setStr("No server.");
  else
    {
      std::stringstream ss;
      ss << core.serverAddr.second;
      buttons[0].setStr("Connected to " + core.serverAddr.first + ":" + ss.str());
    }
  if (core.pc == NULL)
    buttons[2].setStr("No character.");
  else
    buttons[2].setStr(core.pc->getName());
  drawButtons();

  if (static_cast<WaitPacket *>(submenus[3])->receivedValue())
    receivedStartgame();
}

void
gauntlet::core::Lobby::undraw()
{
  undrawButtons();
}

void
gauntlet::core::Lobby::doButton(int btnId, struct t_hitItem & item)
{
  (this->*(funs[btnId]))(item);
}

void
gauntlet::core::Lobby::doServer(struct t_hitItem & item)
{
  if (core.packetf == NULL)
    static_cast<TextBox *>(submenus[2])->setText("38424");
  submenus[2]->setOpen(true);
}

void
gauntlet::core::Lobby::doCharacter(struct t_hitItem & item)
{
  if (core.packetf == NULL)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg
	("You must first connect to a server.");
      submenus[0]->setOpen(true);
    }
  else
    {
      if (core.pc == NULL)
	static_cast<TextBox *>(submenus[1])->setText("Hero");
      else
	static_cast<TextBox *>(submenus[1])->setText(core.pc->getName());
      submenus[1]->setOpen(true);
    }
}

void
gauntlet::core::Lobby::doPlay(struct t_hitItem & item)
{
  (void)item;
  if (core.pc == NULL)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg
	("You must first create your character.");
      submenus[0]->setOpen(true);
    }
  else if (core.packetf == NULL)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg
	("You must first connect to a server.");
      submenus[0]->setOpen(true);
    }

  else
    {
      network::PacketSelectPlayer psp(core.pc->getChar() == world::BARBARIAN,
				      core.pc->getChar() == world::MAGE,
				      core.pc->getChar() == world::VALKYRIE,
				      core.pc->getChar() == world::RANGER,
				      core.pc->getName());
      core.packetf->send(psp);
      submenus[3]->setOpen(true);
    }
}

void
gauntlet::core::Lobby::receivedStartgame()
{
  network::PacketStartGame const * packet =
    dynamic_cast<network::PacketStartGame const *>
    (static_cast<WaitPacket *>(submenus[3])->getReceived());
  if (packet != NULL)
    {
      if (core.ogre.entityExist(packet->getEntityId()))
        core.ogre.addCameraTracker(packet->getEntityId());
      else
        core.actionlists.setCameraTrackerId(packet->getEntityId());
      core.play();
    }
  else
    {
      static_cast<MessageBox *>(submenus[0])->setMsg("No response from server.");
      submenus[0]->setOpen(true);
      core.disconnect(true);
    }
}

void
gauntlet::core::Lobby::doCancel(struct t_hitItem & item)
{
  (void)item;
  setOpen(false);
}
