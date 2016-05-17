//
// MainMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Tue May 17 15:13:16 2016 Esteban Lewis
//

#include <iostream>
#include "MainMenu.hh"

gauntlet::core::MainMenu::MainMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  buttons.push_back(MenuButton("Play", PCENTER, idStart + 0));
  buttons.push_back(MenuButton("Save / load", PCENTER, idStart + 1));
  buttons.push_back(MenuButton("Settings", PCENTER, idStart + 2));
  buttons.push_back(MenuButton("Exit", PCENTER, idStart + 3));
  
  funs.insert(std::pair<int, void (MainMenu::*)()>
	      (buttons[0].getId(), &MainMenu::doPlay));
  funs.insert(std::pair<int, void (MainMenu::*)()>
	      (buttons[1].getId(), &MainMenu::doSaveload));
  funs.insert(std::pair<int, void (MainMenu::*)()>
	      (buttons[2].getId(), &MainMenu::doSettings));
  funs.insert(std::pair<int, void (MainMenu::*)()>
	      (buttons[3].getId(), &MainMenu::doExit));

  submenus.push_back(new SaveloadMenu(core, idStart + 100, this));
  submenus.push_back(new ConfMenu(core, idStart + 100, this));
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
gauntlet::core::MainMenu::doButton(int btnId)
{
  (this->*(funs[btnId]))();
}

void
gauntlet::core::MainMenu::doPlay()
{
  setOpen(false);
  core.play();
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
gauntlet::core::MainMenu::doExit()
{
  setOpen(false);
  core.exit();
}
