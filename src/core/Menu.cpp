//
// Menu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:17:57 2016 Esteban Lewis
// Last update Sat May 21 14:24:56 2016 Esteban Lewis
//

#include "Menu.hh"

gauntlet::core::Menu::Menu(Core & core, int idStart, Menu * parent) :
  idStart(idStart), core(core), isOpen(false), parent(parent)
{ }

gauntlet::core::Menu::~Menu()
{
  for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
    delete *it;
}

bool
gauntlet::core::Menu::keyDown(Command key)
{
  if (!isOpen)
    return (false);

  for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
    if (*it && (*it)->getOpen())
      {
	(*it)->keyDown(key);
	return (true);
      }

  if (key == ESC)
    {
      setOpen(false);
    }
  return (true);
}

bool
gauntlet::core::Menu::buttonClick(int buttonId, struct t_hitItem & item)
{
  if (!isOpen)
    return (false);

  for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
    if (*it && (*it)->getOpen())
      {
	(*it)->buttonClick(buttonId, item);
	return (true);
      }
  doButton(buttonId, item);
  return (true);
}

void
gauntlet::core::Menu::setOpen(bool open)
{
  isOpen = open;
  if (isOpen)
    {
      if (parent)
	parent->undraw();
      draw();
    }
  else
    {
      for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
	{
	  if ((*it)->getOpen() == true)
	    (*it)->setOpen(false);
	}
      undraw();
      if (parent)
	parent->draw();
    }
}

bool
gauntlet::core::Menu::getOpen()
{
  return (isOpen);
}

void
gauntlet::core::Menu::drawButtons()
{
  for (std::vector<Control>::iterator it = buttons.begin(); it != buttons.end(); ++it)
    {
      it->draw();
    }
}

void
gauntlet::core::Menu::undrawButtons()
{
  for (std::vector<Control>::iterator it = buttons.begin(); it != buttons.end(); ++it)
    {
      it->undraw();
    }
}
