//
// SaveloadMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Mon May 23 22:46:20 2016 Esteban Lewis
//

#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include "SaveloadMenu.hh"
#include "MessageBox.hh"

gauntlet::core::SaveloadMenu::SaveloadMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  buttons.push_back(Control(BUTTON, "\t\tReturn\t\t", NULL, PCENTER, idStart, core.ogre));
  buttons.push_back(Control(LABEL, " Maps ", NULL, PCENTER, idStart + 1, core.ogre));

  funs.insert(std::pair<int, void (SaveloadMenu::*)(struct t_hitItem &)>
	      (buttons[0].getId(), &SaveloadMenu::doReturn));

  selected = NEW_SAVE;
  getSaves();

  /*funs.insert(std::pair<int, void (SaveloadMenu::*)(struct t_hitItem &)>
	      (idStart + buttons.size(), &SaveloadMenu::doSave));
  buttons.push_back(Control(BUTTON, "Save", NULL, PCENTER, idStart + buttons.size(),
  core.ogre));*/

  funs.insert(std::pair<int, void (SaveloadMenu::*)(struct t_hitItem &)>
	      (idStart + buttons.size(), &SaveloadMenu::doLoad));
  buttons.push_back(Control(BUTTON, "Load", NULL, PCENTER, idStart + buttons.size(),
			    core.ogre));

  submenus.push_back(new MessageBox(core, idStart + MENU_ID_LAYER, this, ""));
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
gauntlet::core::SaveloadMenu::doButton(int btnId, struct t_hitItem & item)
{
  (this->*(funs[btnId]))(item);
}

void
gauntlet::core::SaveloadMenu::getSaves()
{
  funs.insert(std::pair<int, void (SaveloadMenu::*)(struct t_hitItem &)>
	      (idStart + buttons.size(), &SaveloadMenu::doSelect));

  DIR * dir = opendir(SAVE_DIR);
  if (dir == NULL)
    return ;
  struct dirent * ent;
  //saves.push_back(NEW_SAVE);
  while ((ent = readdir(dir)) != NULL)
    {
      if (ent->d_name[0] != '.')
	saves.push_back(std::string(ent->d_name));
    }
  closedir(dir);
  if (saves.size() > 0)
    selected = saves[0];
  else
    selected = NEW_SAVE;

  buttons.push_back(Control(SELECTMENU, "", &saves, PCENTER,
			    idStart + buttons.size(), core.ogre));
}

void
gauntlet::core::SaveloadMenu::message(std::string const & msg)
{
  static_cast<MessageBox *>(submenus[0])->setMsg(msg);
  submenus[0]->setOpen(true);
}

void
gauntlet::core::SaveloadMenu::doSelect(struct t_hitItem & item)
{
  selected = item.data;
}

void
gauntlet::core::SaveloadMenu::doSave(struct t_hitItem & item)
{
  (void)item;
  setOpen(false);
  core.save(selected);
}

void
gauntlet::core::SaveloadMenu::doLoad(struct t_hitItem & item)
{
  (void)item;
  if (selected == NEW_SAVE)
    message("Please select which game to load.");
  else
    {
      setOpen(false);
      core.load(selected);
    }
}

void
gauntlet::core::SaveloadMenu::doReturn(struct t_hitItem & item)
{
  (void)item;
  setOpen(false);
}
