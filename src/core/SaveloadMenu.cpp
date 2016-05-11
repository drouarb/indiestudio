//
// SaveloadMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Wed May 11 13:50:33 2016 Esteban Lewis
//

#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include "SaveloadMenu.hh"

gauntlet::core::SaveloadMenu::SaveloadMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart), parent(parent)
{
  buttons.push_back(MenuButton("Return", 0, 0, idStart));
  buttons.push_back(MenuButton("Save", 0, 50, idStart + 1));
  buttons.push_back(MenuButton("Load", 100, 50, idStart + 2));

  funs.insert(std::pair<int, void (SaveloadMenu::*)(Command)>
	      (0, &SaveloadMenu::doReturn));
  funs.insert(std::pair<int, void (SaveloadMenu::*)(Command)>
	      (1, &SaveloadMenu::doSave));
  funs.insert(std::pair<int, void (SaveloadMenu::*)(Command)>
	      (2, &SaveloadMenu::doLoad));

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
gauntlet::core::SaveloadMenu::doButton(Command key)
{
  if (key == ENTER)
    (this->*(funs[cursor]))(key);
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
	  buttons.push_back(MenuButton(ent->d_name, 0, id * 30, idStart + id));
	  funs.insert(std::pair<int, void (SaveloadMenu::*)(Command)>
		      (id, &SaveloadMenu::doSelect));
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
gauntlet::core::SaveloadMenu::doSelect(Command key)
{
  (void)key;
  if (selected == &(buttons[cursor]))
    selected = NULL;
  else
    selected = &(buttons[cursor]);
  //TODO: visuals on selected button
}

void
gauntlet::core::SaveloadMenu::doSave(Command key)
{
  (void)key;
  setOpen(false);
  if (selected == NULL)
    core.save("");
  else
    core.save(selected->getStr());
}

void
gauntlet::core::SaveloadMenu::doLoad(Command key)
{
  (void)key;
  if (selected == NULL)
    message("Please select which game to load.");
  else
    {
      parent->setOpen(false);
      core.load(selected->getStr());
    }
}

void
gauntlet::core::SaveloadMenu::doReturn(Command key)
{
  (void)key;
  setOpen(false);
}
