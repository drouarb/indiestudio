#include "CharMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "PlayerController.hh"

gauntlet::core::CharMenu::CharMenu(Core &core, int idStart, Menu *parent) :
        TextBox(core, idStart, parent, "Name")
{
    charType = world::BARBARIAN;
    barbarian = true;
    valkyrie = true;
    ranger = true;
    wizard = true;

    submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::CharMenu::~CharMenu()
{ }

void
gauntlet::core::CharMenu::draw()
{
    if (barbarian)
       charTypes.push_back("Barbarian");
    if (ranger)
        charTypes.push_back("Ranger");
    if (wizard)
        charTypes.push_back("Wizard");
    if (valkyrie)
        charTypes.push_back("Valkyrie");

    buttons.push_back(Control(SELECTMENU, "Class: ", &charTypes, PCENTER,
                              idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (CharMenu::*)(struct t_hitItem &)>
                        (buttons[buttons.size() - 1].getId(), &CharMenu::doChartype));

    buttons.push_back(Control(BUTTON, "OK", NULL, PCENTER,
                              idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (CharMenu::*)(struct t_hitItem &)>
                        (buttons[buttons.size() - 1].getId(), &CharMenu::doOk));

    buttons.push_back(Control(BUTTON, "Cancel", NULL, PCENTER,
                              idStart + buttons.size(), core.ogre));
    funs.insert(std::pair<int, void (CharMenu::*)(struct t_hitItem &)>
                        (buttons[buttons.size() - 1].getId(), &CharMenu::doCancel));

    drawButtons();
    core.ogre.showCharacterSelectMenu(BERSERKER_MENU_SELECTION);
    if (!core.gameIsRunning())
        core.ogre.showBackground(BACKGROUND_HELL);
}

void
gauntlet::core::CharMenu::undraw()
{
    undrawButtons();
    core.ogre.hideCharacterSelectMenu();
    buttons.clear();
    charTypes.clear();
    funs.clear();
}

void
gauntlet::core::CharMenu::doButton(int btnId, struct t_hitItem &item)
{
    (this->*(funs[btnId]))(item);
}

void
gauntlet::core::CharMenu::doChartype(struct t_hitItem &item)
{
    if (item.data == "Barbarian")
        {
            charType = world::BARBARIAN;
            core.ogre.showCharacterSelectMenu(BERSERKER_MENU_SELECTION);
        }
    else if (item.data == "Ranger")
        {
            charType = world::RANGER;
            core.ogre.showCharacterSelectMenu(RANGER_MENU_SELECTION);
        }
    else if (item.data == "Wizard")
        {
            charType = world::MAGE;
            core.ogre.showCharacterSelectMenu(MAGUS_MENU_SELECTION);
        }
    else if (item.data == "Valkyrie")
        {
            charType = world::VALKYRIE;
            core.ogre.showCharacterSelectMenu(VALKYRIE_MENU_SELECTION);
        }
}

void
gauntlet::core::CharMenu::doOk(struct t_hitItem &item)
{
    (void) item;
    if (text.length() == 0)
        {
            static_cast<MessageBox *>(submenus[0])->setMsg("Please enter a name.");
            submenus[0]->setOpen(true);
        }
    else
        {
            if (core.pc)
                delete (core.pc);
            core.pc = new PlayerController(text, charType, core);
            setOpen(false);
        }
}

void
gauntlet::core::CharMenu::doCancel(struct t_hitItem &item)
{
    (void) item;
    setOpen(false);
}
