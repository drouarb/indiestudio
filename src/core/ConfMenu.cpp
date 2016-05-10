//
// ConfMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Tue May 10 16:44:12 2016 Esteban Lewis
//

#include <iostream>
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
  
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (0, &ConfMenu::doReturn));
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (1, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (2, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (3, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (4, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (5, &ConfMenu::doKeylink));
  funs.insert(std::pair<int, void (ConfMenu::*)(IUIObserver::Key)>
	      (6, &ConfMenu::doKeylink));
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
gauntlet::core::ConfMenu::keyDown(IUIObserver::Key key)
{
  if (!isOpen)
    return (false);

  if (waitForKey)
    {
      core.getConf().setKey((IUIObserver::Key)cursor, key);
      waitForKey = false;
      return (true);
    }
  else
    {
      return (Menu::keyDown(key));
    }
}

void
gauntlet::core::ConfMenu::doButton(IUIObserver::Key key)
{
  if (key == IUIObserver::KEY_ENTER)
    (this->*(funs[cursor]))(key);
}

void
gauntlet::core::ConfMenu::doReturn(IUIObserver::Key key)
{
  (void)key;
  setOpen(false);
}

void
gauntlet::core::ConfMenu::doKeylink(IUIObserver::Key key)
{
  (void)key;
  waitForKey = true;
  //TODO: visuals
}
