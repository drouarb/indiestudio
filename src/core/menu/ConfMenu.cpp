//
// ConfMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Wed May 25 22:14:12 2016 Esteban Lewis
//

#include "ConfMenu.hh"
#include "Core.hh"
#include "KeyMenu.hh"

gauntlet::core::ConfMenu::ConfMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doReturn));
  buttons.push_back(Control(BUTTON, "- Return -", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));


  buttons.push_back(Control(LABEL, "Graphics:", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));

  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doParticles));
  buttons.push_back(Control(SLIDE, "Particles", (void*)(new int(100)), PCENTER,
			    idStart + buttons.size(), core.ogre));


  buttons.push_back(Control(LABEL, "Controls:", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));

  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Go forward", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Go backward", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Go left", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Go right", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Validate", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Menu", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Normal attack", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Special ability", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Extra ability 1", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  funs.insert(std::pair<int, void (ConfMenu::*)(int, struct t_hitItem &)>
	      (buttons.size() + idStart, &ConfMenu::doKeylink));
  buttons.push_back(Control(BUTTON, "Extra ability 2", NULL, PCENTER,
			    idStart + buttons.size(), core.ogre));
  


  // KEY NAMES

  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_NONE, ""));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_UP, "Arrow up"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_DOWN, "Arrow down"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_LEFT, "Arrow left"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_RIGHT, "Arrow right"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_ENTER, "Enter"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_ESC, "Escape"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_MOUSE1, "Left mouse button"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_MOUSE2, "Right mouse button"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_TAB, "Tabulation"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_SPACE, "Spacebar"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_BACK, "Backspace"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_A, "A"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_B, "B"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_C, "C"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_D, "D"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_E, "E"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_F, "F"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_G, "G"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_H, "H"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_I, "I"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_J, "J"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_K, "K"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_L, "L"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_M, "M"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_N, "N"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_O, "O"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_P, "P"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_Q, "Q"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_R, "R"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_S, "S"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_T, "T"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_U, "U"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_V, "V"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_W, "W"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_X, "X"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_Y, "Y"));
  keyNames.insert(std::pair<IUIObserver::Key, std::string>
		  (IUIObserver::KEY_Z, "Z"));

  submenus.push_back(new KeyMenu(core, idStart + MENU_ID_LAYER, this));
}

gauntlet::core::ConfMenu::~ConfMenu()
{ }

void
gauntlet::core::ConfMenu::draw()
{
  drawButtons();

  struct t_hitItem item;
  item.value = core.ogre.getQuality();
  buttons[2].update(item);
}

void
gauntlet::core::ConfMenu::undraw()
{
  undrawButtons();
}

std::string const &
gauntlet::core::ConfMenu::getKeyName(IUIObserver::Key key)
{
  for (std::map<IUIObserver::Key, std::string>::iterator it = keyNames.begin();
       it != keyNames.end(); ++it)
    {
      if (it->first == key)
	return (it->second);
    }
  return (keyNames.begin()->second);
}

gauntlet::core::IUIObserver::Key
gauntlet::core::ConfMenu::getNameKey(std::string const & name)
{
  for (std::map<IUIObserver::Key, std::string>::iterator it = keyNames.begin();
       it != keyNames.end(); ++it)
    {
      if (it->second == name)
	return (it->first);
    }
  return (keyNames.begin()->first);
}

void
gauntlet::core::ConfMenu::doButton(int btnId, struct t_hitItem & item)
{
  (this->*(funs[btnId]))(btnId, item);
}

void
gauntlet::core::ConfMenu::doReturn(int btnId, struct t_hitItem & item)
{
  (void)btnId;
  (void)item;
  setOpen(false);
}

void
gauntlet::core::ConfMenu::doKeylink(int btnId, struct t_hitItem & item)
{
  (void)item;
  static_cast<KeyMenu*>(submenus[0])->setCmd((Command)(btnId - idStart - 1));
  submenus[0]->setOpen(true);
}

void
gauntlet::core::ConfMenu::doParticles(int btnId, struct t_hitItem & item)
{
  (void)btnId;
  core.ogre.setQuality(item.value);
}
