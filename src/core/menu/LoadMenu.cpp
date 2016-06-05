#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include "LoadMenu.hh"
#include "MessageBox.hh"

gauntlet::core::LoadMenu::LoadMenu(Core &core, int idStart, Menu *parent) :
        Menu(core, idStart, parent)
{
    submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::LoadMenu::~LoadMenu()
{ }

void
gauntlet::core::LoadMenu::draw()
{
    buttons.push_back(Control(BUTTON, "\t\tReturn\t\t", NULL, PCENTER, idStart, core.ogre));
    buttons.push_back(Control(LABEL, " Maps ", NULL, PCENTER, idStart + 1, core.ogre));

    funs.insert(std::pair<int, void (LoadMenu::*)(struct t_hitItem &)>
                        (buttons[0].getId(), &LoadMenu::doReturn));

    selected = NEW_SAVE;
    getSaves();

    funs.insert(std::pair<int, void (LoadMenu::*)(struct t_hitItem &)>
                        (idStart + buttons.size(), &LoadMenu::doLoad));
    buttons.push_back(Control(BUTTON, "Load", NULL, PCENTER, idStart + buttons.size(),
                              core.ogre));

    drawButtons();
}

void
gauntlet::core::LoadMenu::undraw()
{
    undrawButtons();

    buttons.clear();
    funs.clear();
    saves.clear();
}

void
gauntlet::core::LoadMenu::doButton(int btnId, struct t_hitItem &item)
{
    (this->*(funs[btnId]))(item);
}

void
gauntlet::core::LoadMenu::getSaves()
{
    funs.insert(std::pair<int, void (LoadMenu::*)(struct t_hitItem &)>
                        (idStart + buttons.size(), &LoadMenu::doSelect));

    DIR *dir = opendir(SAVE_DIR);
    if (dir == NULL)
        return;
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.')
                saves.push_back(std::string(ent->d_name));
        }
    closedir(dir);
    if (saves.size() > 0)
        selected = saves[0];
    else
        selected = NEW_SAVE;

    buttons.push_back(Control(SELECTMENU, "", &saves, PCENTER,
                              idStart + buttons.size(), core.ogre));
}

void
gauntlet::core::LoadMenu::message(std::string const &msg)
{
    static_cast<MessageBox *>(submenus[0])->setMsg(msg);
    submenus[0]->setOpen(true);
}

void
gauntlet::core::LoadMenu::doSelect(struct t_hitItem &item)
{
    selected = item.data;
}

void
gauntlet::core::LoadMenu::doLoad(struct t_hitItem &item)
{
    (void) item;
    if (selected == NEW_SAVE)
        message("Please select which game to load.");
    else
        {
            setOpen(false);
            core.load(selected);
        }
}

void
gauntlet::core::LoadMenu::doReturn(struct t_hitItem &item)
{
    (void) item;
    setOpen(false);
}
