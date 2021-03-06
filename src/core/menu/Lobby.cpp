#include <sstream>
#include <network/packet/PacketHandshake.hh>
#include "Lobby.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "CharMenu.hh"
#include "ConnectMenu.hh"
#include "PacketSelectPlayer.hh"
#include "PacketStartGame.hh"
#include "WaitPacket.hh"
#include "PlayerController.hh"
#include "PacketFactory.hh"

gauntlet::core::Lobby::Lobby(Core &core, int idStart, Menu *parent) :
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

    if (!core.gameIsRunning())
        core.ogre.showBackground(BACKGROUND_DOOR);

    if (static_cast<WaitPacket *>(submenus[3])->receivedValue())
        receivedStartgame();
}

void
gauntlet::core::Lobby::undraw()
{
    undrawButtons();
}

void
gauntlet::core::Lobby::doButton(int btnId, struct t_hitItem &item)
{
    (this->*(funs[btnId]))(item);
}

void
gauntlet::core::Lobby::doServer(struct t_hitItem &item)
{
    if (core.packetf == NULL)
        static_cast<TextBox *>(submenus[2])->setText("38424");
    submenus[2]->setOpen(true);
}

void
gauntlet::core::Lobby::doCharacter(struct t_hitItem &item)
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
gauntlet::core::Lobby::doPlay(struct t_hitItem &item)
{
    (void) item;
    core.networkmutex.lock();
    if (core.pc == NULL)
        {
            core.networkmutex.unlock();
            static_cast<MessageBox *>(submenus[0])->setMsg
                    ("You must first create your character.");
            submenus[0]->setOpen(true);
        }
    else if (core.packetf == NULL)
        {
            core.networkmutex.unlock();
            static_cast<MessageBox *>(submenus[0])->setMsg
                    ("You must first connect to a server.");
            submenus[0]->setOpen(true);
        }
    else if (core.gameIsRunning())
        {
            core.networkmutex.unlock();
            static_cast<MessageBox *>(submenus[0])->setMsg
                    ("You must connect to a new server to start a new game.");
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
            core.networkmutex.unlock();
            submenus[3]->setOpen(true);
        }
}

void
gauntlet::core::Lobby::receivedStartgame()
{
    network::Packet const *packet =
            (static_cast<WaitPacket *>(submenus[3])->getReceived());

    network::PacketStartGame const *startgame =
            dynamic_cast<network::PacketStartGame const *>(packet);
    if (startgame != NULL)
        {
            if (core.ogre.entityExist(startgame->getEntityId()))
                core.ogre.addCameraTracker(startgame->getEntityId());
            else
                core.actionlists.setCameraTrackerId(startgame->getEntityId());
            core.play();
        }
    else
        {
            network::PacketHandshake const *handshake =
                    dynamic_cast<network::PacketHandshake const *>(packet);
            if (handshake != NULL)
                {
                    static_cast<MessageBox *>(submenus[0])->setMsg("Chosen character is unavailable.");
                    submenus[0]->setOpen(true);
                    setChars(handshake);
                }
            else
                {
                    static_cast<MessageBox *>(submenus[0])->setMsg("No response from server.");
                    submenus[0]->setOpen(true);
                }
        }
}

void
gauntlet::core::Lobby::doCancel(struct t_hitItem &item)
{
    (void) item;
    setOpen(false);
}

void gauntlet::core::Lobby::setChars(network::PacketHandshake const *handshake)
{
    static_cast<CharMenu *>(submenus[1])->barbarian = handshake->getWarrior();
    static_cast<CharMenu *>(submenus[1])->wizard = handshake->getWizard();
    static_cast<CharMenu *>(submenus[1])->ranger = handshake->getElf();
    static_cast<CharMenu *>(submenus[1])->valkyrie = handshake->getValkyrie();
}


