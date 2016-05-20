//
// ConfMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Fri May 20 23:24:53 2016 Esteban Lewis
//

#include "ConfMenu.hh"
#include "Core.hh"

gauntlet::core::ConfMenu::ConfMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  cmdToSet = NONE;

  buttons.push_back(MenuButton("- Return -", PCENTER, idStart, core.getGui()));

  buttons.push_back(MenuButton("Go forward", PCENTER, idStart + 1, core.getGui()));
  buttons.push_back(MenuButton("Go backward", PCENTER, idStart + 2, core.getGui()));
  buttons.push_back(MenuButton("Go left", PCENTER, idStart + 3, core.getGui()));
  buttons.push_back(MenuButton("Go right", PCENTER, idStart + 4, core.getGui()));
  buttons.push_back(MenuButton("Validate", PCENTER, idStart + 5, core.getGui()));
  buttons.push_back(MenuButton("Exit", PCENTER, idStart + 6, core.getGui()));
  
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[0].getId(), &ConfMenu::doReturn));
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[1].getId(), &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[2].getId(), &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[3].getId(), &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[4].getId(), &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[5].getId(), &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(int)>
	      (buttons[6].getId(), &ConfMenu::doKeylink));


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
}

gauntlet::core::ConfMenu::~ConfMenu()
{ }

void
gauntlet::core::ConfMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::ConfMenu::undraw()
{
  undrawButtons();
}

bool
gauntlet::core::ConfMenu::keyDown(Command key)
{
  if (!isOpen)
    return (false);

  if (cmdToSet != NONE)
    {
      core.getConf().setKey(cmdToSet, core.getConf().getLinkedCommand(key));
      cmdToSet = NONE;
      return (true);
    }
  else
    {
      return (Menu::keyDown(key));
    }
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
gauntlet::core::ConfMenu::doButton(int btnId)
{
  (this->*(funs[btnId]))(btnId);
}

void
gauntlet::core::ConfMenu::doReturn(int btnId)
{
  (void)btnId;
  setOpen(false);
}

void
gauntlet::core::ConfMenu::doKeylink(int btnId)
{
  cmdToSet = (Command)(btnId - idStart);
  //TODO: visuals
}
