#include "CharMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "PlayerController.hh"
#include "CharacterMenuName.hh"

gauntlet::core::CharMenu::CharMenu(Core &core, int idStart, Menu *parent) :
        TextBox(core, idStart, parent, "Name")
{
    charType = world::BARBARIAN;
    charTypes.push_back("Barbarian");
    charTypes.push_back("Ranger");
    charTypes.push_back("Mage");
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

    submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::CharMenu::~CharMenu()
{ }

void
gauntlet::core::CharMenu::draw()
{
    drawButtons();
    core.ogre.showCharacterSelectMenu(BERSERKER_MENU_SELECTION);
}

void
gauntlet::core::CharMenu::undraw()
{
    undrawButtons();
    core.ogre.hideCharacterSelectMenu();
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
    else if (item.data == "Mage")
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
