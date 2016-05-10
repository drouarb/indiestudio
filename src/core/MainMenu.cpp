//
// MainMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Tue May 10 15:59:42 2016 Esteban Lewis
//

#include <iostream>
#include "MainMenu.hh"

gauntlet::core::MainMenu::MainMenu(Core & core, int idStart) : Menu(core, idStart)
{
  buttons.push_back(MenuButton("Play", 0, 0, idStart + 0));
  buttons.push_back(MenuButton("Save / load", 0, 50, idStart + 1));
  buttons.push_back(MenuButton("Settings", 0, 100, idStart + 2));
  buttons.push_back(MenuButton("Exit", 0, 150, idStart + 3));
  
  funs.insert(std::pair<int, void (MainMenu::*)(IUIObserver::Key)>
	      (0, &MainMenu::doPlay));
  funs.insert(std::pair<int, void (MainMenu::*)(IUIObserver::Key)>
	      (1, &MainMenu::doSaveload));
  funs.insert(std::pair<int, void (MainMenu::*)(IUIObserver::Key)>
	      (2, &MainMenu::doSettings));
  funs.insert(std::pair<int, void (MainMenu::*)(IUIObserver::Key)>
	      (3, &MainMenu::doExit));

  submenus.push_back(new SaveloadMenu(core, idStart + 100, this));
  submenus.push_back(new ConfMenu(core, idStart + 100));
}

gauntlet::core::MainMenu::~MainMenu()
{ }

void
gauntlet::core::MainMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::MainMenu::undraw()
{
  undrawButtons();
}

void
gauntlet::core::MainMenu::doButton(IUIObserver::Key key)
{
  if (key == IUIObserver::KEY_ENTER)
    (this->*(funs[cursor]))(key);
}

void
gauntlet::core::MainMenu::doPlay(IUIObserver::Key key)
{
  (void)key;
  setOpen(false);
  core.play();
}

void
gauntlet::core::MainMenu::doSaveload(IUIObserver::Key key)
{
  (void)key;
  submenus[MENU_SL]->setOpen(true);
}

void
gauntlet::core::MainMenu::doSettings(IUIObserver::Key key)
{
  (void)key;
  submenus[MENU_CONFIG]->setOpen(true);
}

void
gauntlet::core::MainMenu::doExit(IUIObserver::Key key)
{
  (void)key;
  setOpen(false);
  core.exit();
}
