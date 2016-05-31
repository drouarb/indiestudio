//
// MainMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Thu May 26 14:44:34 2016 Esteban Lewis
//

#include <iostream>
#include "MainMenu.hh"
#include "Lobby.hh"
#include "ConfMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "SaveloadMenu.hh"

gauntlet::core::MainMenu::MainMenu(Core &core, int idStart, Menu *parent) :
        Menu(core, idStart, parent)
{
    submenus.push_back(new SaveloadMenu(core, idStart + MENU_ID_LAYER, this));
    submenus.push_back(new ConfMenu(core, idStart + MENU_ID_LAYER, this));
    submenus.push_back(new Lobby(core, idStart + MENU_ID_LAYER, this));
    submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::MainMenu::~MainMenu()
{ }

void
gauntlet::core::MainMenu::draw()
{
    buttons = std::vector<Control>();
    funs.clear();

    if (core.gameIsRunning())
        {
            buttons.push_back(Control(BUTTON, "Continue", NULL, PCENTER, idStart + buttons.size(), core.ogre));
            funs.insert(std::pair<int, void (MainMenu::*)()>
                                (buttons[buttons.size() - 1].getId(), &MainMenu::doContinue));
        }

    buttons.push_back(Control(BUTTON, "Start game", NULL, PCENTER, idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (MainMenu::*)()>
                        (buttons[buttons.size() - 1].getId(), &MainMenu::doPlay));

    buttons.push_back(Control(BUTTON, "Load map", NULL, PCENTER, idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (MainMenu::*)()>
                        (buttons[buttons.size() - 1].getId(), &MainMenu::doSaveload));

    buttons.push_back(Control(BUTTON, "Settings", NULL, PCENTER, idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (MainMenu::*)()>
                        (buttons[buttons.size() - 1].getId(), &MainMenu::doSettings));

    buttons.push_back(Control(BUTTON, "Exit", NULL, PCENTER, idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (MainMenu::*)()>
                        (buttons[buttons.size() - 1].getId(), &MainMenu::doExit));


    drawButtons();

    if (!core.gameIsRunning())
        core.ogre.showBackground(BACKGROUND_BASIC);
}

void
gauntlet::core::MainMenu::undraw()
{
    undrawButtons();
}

bool
gauntlet::core::MainMenu::keyDown(Command cmd)
{
    if (!isOpen)
        return (false);

    if (cmd == ESC && !core.gameIsRunning())
        {
            bool openSubmenu = false;

            for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
                if (*it && (*it)->getOpen())
                    {
                        openSubmenu = true;
                        break;
                    }

            if (!openSubmenu)
                {
                    //no open submenu to redirect the command to, no game to go back to -> do nothing
                    return (true);
                }
        }

    return (Menu::keyDown(cmd));
}

void
gauntlet::core::MainMenu::message(std::string const &msg)
{
    static_cast<MessageBox *>(submenus[3])->setMsg(msg);
    submenus[3]->setOpen(true);
}

void
gauntlet::core::MainMenu::doButton(int btnId, struct t_hitItem &item)
{
    (this->*(funs[btnId]))();
}

void
gauntlet::core::MainMenu::doPlay()
{
    submenus[MENU_LOBBY]->setOpen(true);
}

void
gauntlet::core::MainMenu::doSaveload()
{
    submenus[MENU_SL]->setOpen(true);
}

void
gauntlet::core::MainMenu::doSettings()
{
    submenus[MENU_CONFIG]->setOpen(true);
}

void
gauntlet::core::MainMenu::doContinue()
{
    setOpen(false);
}

void
gauntlet::core::MainMenu::doExit()
{
    setOpen(false);
    core.exit();
}
