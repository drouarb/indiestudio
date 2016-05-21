//
// MainMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Sat May 21 11:43:11 2016 Esteban Lewis
//

#include <iostream>
#include "MainMenu.hh"

gauntlet::core::MainMenu::MainMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  buttons.push_back(Control(BUTTON, "Play", NULL, PCENTER, idStart + 0, core.getGui()));
  buttons.push_back(Control(BUTTON, "Save / load", NULL, PCENTER, idStart + 1, core.getGui()));
  buttons.push_back(Control(BUTTON, "Settings", NULL, PCENTER, idStart + 2, core.getGui()));
  buttons.push_back(Control(BUTTON, "Exit", NULL, PCENTER, idStart + 3, core.getGui()));
  
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

bool
gauntlet::core::MainMenu::keyDown(Command cmd)
{
  if (!isOpen)
    return (false);

  if (cmd == ESC /* && there is no running game*/)
    {
      bool openSubmenu = false;

      for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
	if (*it && (*it)->getOpen())
	  {
	    openSubmenu = true;
	    break ;
	  }

      if (!openSubmenu)
	{
	  //no open submenu to redirect the command to, no game to go back to -> do nothing
	  return (true);
	}
    }

  return (Menu::keyDown(cmd));
}

void
gauntlet::core::MainMenu::doButton(int btnId, struct t_hitItem & item)
{
  (void)item;
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
