#include "CharMenu.hh"
#include "MessageBox.hh"
#include "Core.hh"
#include "PlayerController.hh"

gauntlet::core::CharMenu::CharMenu(Core & core, int idStart, Menu * parent) :
  TextBox(core, idStart, parent)
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

  submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
}

gauntlet::core::CharMenu::~CharMenu()
{ }

void
gauntlet::core::CharMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::CharMenu::undraw()
{
  undrawButtons();
}

void
gauntlet::core::CharMenu::doButton(int btnId, struct t_hitItem & item)
{
  (this->*(funs[btnId]))(item);
}

void
gauntlet::core::CharMenu::doChartype(struct t_hitItem & item)
{
  if (item.data == "Barbarian")
    charType = world::BARBARIAN;
  else if (item.data == "Ranger")
    charType = world::RANGER;
  else if (item.data == "Mage")
    charType = world::MAGE;
  else if (item.data == "Valkyrie")
    charType = world::VALKYRIE;
}

void
gauntlet::core::CharMenu::doOk(struct t_hitItem & item)
{
  (void)item;
  if (charType == world::NOCHAR)
    {
      static_cast<MessageBox *>(submenus[0])->setMsg("Please select a class.");
      submenus[0]->setOpen(true);
    }
  else
    {
      if (core.pc)
	delete (core.pc);
      core.pc = new PlayerController("", charType);
      setOpen(false);
    }
}
