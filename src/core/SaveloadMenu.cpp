//
// SaveloadMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Fri May 20 23:26:55 2016 Esteban Lewis
//

#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include "SaveloadMenu.hh"

gauntlet::core::SaveloadMenu::SaveloadMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  buttons.push_back(MenuButton("Return", PCENTER, idStart, core.getGui()));
  buttons.push_back(MenuButton("Save", PCENTER, idStart + 1, core.getGui()));
  buttons.push_back(MenuButton("Load", PCENTER, idStart + 2, core.getGui()));

  funs.insert(std::pair<int, void (SaveloadMenu::*)(int)>
	      (buttons[0].getId(), &SaveloadMenu::doReturn));
  funs.insert(std::pair<int, void (SaveloadMenu::*)(int)>
	      (buttons[1].getId(), &SaveloadMenu::doSave));
  funs.insert(std::pair<int, void (SaveloadMenu::*)(int)>
	      (buttons[2].getId(), &SaveloadMenu::doLoad));

  selected = NULL;
  getSaves();
}

gauntlet::core::SaveloadMenu::~SaveloadMenu()
{ }

void
gauntlet::core::SaveloadMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::SaveloadMenu::undraw()
{
  undrawButtons();
}

void
gauntlet::core::SaveloadMenu::doButton(int btnId)
{
  (this->*(funs[btnId]))(btnId);
}

void
gauntlet::core::SaveloadMenu::getSaves()
{
  DIR * dir = opendir(SAVE_DIR);
  if (dir == NULL)
    return ;

  unsigned int id = buttons.size();
  struct dirent * ent;
  while ((ent = readdir(dir)) != NULL)
    {
      //TODO: space problem
      if (ent->d_name[0] != '.')
	{
	  buttons.push_back(MenuButton(ent->d_name, PCENTER, idStart + id, core.getGui()));
	  funs.insert(std::pair<int, void (SaveloadMenu::*)(int)>
		      (buttons[(int)buttons.size() - 1].getId(), &SaveloadMenu::doSelect));
	  id++;
	}
    }
  closedir(dir);
}

void
gauntlet::core::SaveloadMenu::message(std::string const & msg)
{
  std::cout << "Saveload msg " << msg << std::endl;
}

void
gauntlet::core::SaveloadMenu::doSelect(int btnId)
{
  for (std::vector<MenuButton>::iterator it = buttons.begin();
       it != buttons.end(); ++it)
    {
      if (it->getId() == btnId)
	{
	  if (selected == &(*it))
	    selected = NULL;
	  else
	    selected = &(*it);
	  //TODO: info on selected
	  return ;
	}
    }
  selected = NULL;
}

void
gauntlet::core::SaveloadMenu::doSave(int btnId)
{
  (void)btnId;
  setOpen(false);
  if (selected == NULL)
    core.save("");
  else
    core.save(selected->getStr());
}

void
gauntlet::core::SaveloadMenu::doLoad(int btnId)
{
  (void)btnId;
  if (selected == NULL)
    message("Please select which game to load.");
  else
    {
      setOpen(false);
      //TODO: play?
      core.load(selected->getStr());
    }
}

void
gauntlet::core::SaveloadMenu::doReturn(int btnId)
{
  (void)btnId;
  setOpen(false);
}
