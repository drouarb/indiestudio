//
// KeyMenu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:09:17 2016 Esteban Lewis
// Last update Sun May 22 14:11:01 2016 Esteban Lewis
//

#include "KeyMenu.hh"
#include "Core.hh"

gauntlet::core::KeyMenu::KeyMenu(Core & core, int idStart, Menu * parent) :
  Menu(core, idStart, parent)
{
  cmdToSet = NONE;

  buttons.push_back(Control(LABEL, "Press a key.", NULL, PCENTER, idStart, core.ogre));
}

gauntlet::core::KeyMenu::~KeyMenu()
{ }

void
gauntlet::core::KeyMenu::draw()
{
  drawButtons();
}

void
gauntlet::core::KeyMenu::undraw()
{
  undrawButtons();
}

bool
gauntlet::core::KeyMenu::keyDown(Command key)
{
  if (!isOpen)
    return (false);

  if (cmdToSet != NONE)
    {
      core.conf.setKey(cmdToSet, core.getLastKey());
      cmdToSet = NONE;
      setOpen(false);
    }
  return (true);
}

void
gauntlet::core::KeyMenu::setCmd(Command cmd)
{
  cmdToSet = cmd;
}

void
gauntlet::core::KeyMenu::doButton(int btnId, struct t_hitItem & item)
{
  (void)item;
  (void)btnId;
}
