#include <iostream>
#include "SaveMenu.hh"
#include "MessageBox.hh"
#include "PacketFactory.hh"

gauntlet::core::SaveMenu::SaveMenu(Core &core, int idStart, Menu *parent) :
        TextBox(core, idStart, parent, "save_1.json")
{
    buttons.push_back(Control(BUTTON, "Save", NULL, PCENTER,
                              idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (SaveMenu::*)(struct t_hitItem &)>
                        (buttons[buttons.size() - 1].getId(), &SaveMenu::doSave));

    buttons.push_back(Control(BUTTON, "Cancel", NULL, PCENTER,
                              idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (SaveMenu::*)(struct t_hitItem &)>
                        (buttons[buttons.size() - 1].getId(), &SaveMenu::doReturn));

    submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::SaveMenu::~SaveMenu()
{ }

void
gauntlet::core::SaveMenu::draw()
{
    drawButtons();
}

void
gauntlet::core::SaveMenu::undraw()
{
    undrawButtons();
}

void
gauntlet::core::SaveMenu::doButton(int btnId, struct t_hitItem &item)
{
    (this->*(funs[btnId]))(item);
}

void
gauntlet::core::SaveMenu::doSave(struct t_hitItem &item)
{
    (void) item;
    if (text.length() >= std::string(SAVE_DIR).length()
            && text.substr(0, std::string(SAVE_DIR).length()) == SAVE_DIR)
        text = text.substr(std::string(SAVE_DIR).length());
    
    if (text == "")
        {
            static_cast<MessageBox *>(submenus[0])->setMsg("Please enter the path to save the map to.");
            submenus[0]->setOpen(true);
        }
    else
        {
            core.networkmutex.lock();
            if (core.packetf == NULL)
                {
                    core.networkmutex.unlock();
                    static_cast<MessageBox *>(submenus[0])->setMsg("Disconnected from server.");
                    submenus[0]->setOpen(true);
                }
            else
                {
                    network::PacketMap pm(0, SAVE_DIR + text);

                    core.packetf->send(pm);
                    core.networkmutex.unlock();
                    setOpen(false);
                }
        }
}

void
gauntlet::core::SaveMenu::doReturn(struct t_hitItem &item)
{
    (void) item;
    text = "";
    setOpen(false);
}
