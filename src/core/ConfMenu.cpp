//
// ConfMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Wed May 11 15:04:01 2016 Esteban Lewis
//

#include "ConfMenu.hh"
#include "Core.hh"

gauntlet::core::ConfMenu::ConfMenu(Core & core, int idStart) : Menu(core, idStart)
{
  waitForKey = false;

  buttons.push_back(MenuButton("Return", 0, 0, idStart));

  //make sure corresponding cursor value is equal to original corresponding key
  buttons.push_back(MenuButton("Go forward", 0, 30, idStart + 1));
  buttons.push_back(MenuButton("Go backward", 0, 60, idStart + 2));
  buttons.push_back(MenuButton("Go left", 0, 90, idStart + 3));
  buttons.push_back(MenuButton("Go right", 0, 120, idStart + 4));
  buttons.push_back(MenuButton("Validate", 0, 150, idStart + 5));
  buttons.push_back(MenuButton("Exit", 0, 180, idStart + 6));
  
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (0, &ConfMenu::doReturn));
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (1, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (2, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (3, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (4, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (5, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(Command)>
	      (6, &ConfMenu::doKeylink));


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

  if (waitForKey)
    {
      core.getConf().setKey((Command)cursor, core.getLastKey());
      waitForKey = false;
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

void
gauntlet::core::ConfMenu::doButton(Command key)
{
  if (key == ENTER)
    (this->*(funs[cursor]))(key);
}

void
gauntlet::core::ConfMenu::doReturn(Command key)
{
  (void)key;
  setOpen(false);
}

void
gauntlet::core::ConfMenu::doKeylink(Command key)
{
  (void)key;
  waitForKey = true;
  //TODO: visuals
}
