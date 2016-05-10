//
// SaveloadMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Tue May 10 13:56:45 2016 Esteban Lewis
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

  funs.insert(std::pair<int, void (SaveloadMenu::*)(IUIObserver::Key)>
	      (0, &SaveloadMenu::doReturn));
  funs.insert(std::pair<int, void (SaveloadMenu::*)(IUIObserver::Key)>
	      (1, &SaveloadMenu::doSave));
  funs.insert(std::pair<int, void (SaveloadMenu::*)(IUIObserver::Key)>
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
gauntlet::core::SaveloadMenu::doButton(IUIObserver::Key key)
{
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
	  funs.insert(std::pair<int, void (SaveloadMenu::*)(IUIObserver::Key)>
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
gauntlet::core::SaveloadMenu::doSelect(IUIObserver::Key key)
{
  if (key != IUIObserver::KEY_ENTER)
    return ;

  if (selected == &(buttons[cursor]))
    selected = NULL;
  else
    selected = &(buttons[cursor]);
  //TODO: visuals on selected button
}

void
gauntlet::core::SaveloadMenu::doSave(IUIObserver::Key key)
{
  if (key != IUIObserver::KEY_ENTER)
    return ;

  setOpen(false);
  if (selected == NULL)
    core.save("");
  else
    core.save(selected->getStr());
}

void
gauntlet::core::SaveloadMenu::doLoad(IUIObserver::Key key)
{
  if (key != IUIObserver::KEY_ENTER)
    return ;

  if (selected == NULL)
    message("Please select which game to load.");
  else
    {
      parent->setOpen(false);
      core.load(selected->getStr());
    }
}

void
gauntlet::core::SaveloadMenu::doReturn(IUIObserver::Key key)
{
  if (key != IUIObserver::KEY_ENTER)
    return ;

  setOpen(false);
}
