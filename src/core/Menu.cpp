//
// Menu.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:17:57 2016 Esteban Lewis
// Last update Tue May 10 13:58:31 2016 Esteban Lewis
//

#include "Menu.hh"

gauntlet::core::Menu::Menu(Core & core, int idStart) :
  idStart(idStart), core(core), isOpen(false), cursor(0)
{ }

gauntlet::core::Menu::~Menu()
{
  for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
    delete *it;
}

bool
gauntlet::core::Menu::keyDown(IUIObserver::Key key)
{
  if (!isOpen)
    return (false);

  for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
    if ((*it)->getOpen())
      {
	(*it)->keyDown(key);
	return (true);
      }

  if (key == IUIObserver::KEY_ESC)
    {
      setOpen(false);
    }
  else if (key == IUIObserver::KEY_UP)
    {
      if (cursor > 0)
	moveCursor(cursor - 1);
    }
  else if (key == IUIObserver::KEY_DOWN)
    {
      if (cursor < (int)buttons.size() - 1)
	moveCursor(cursor + 1);
    }
  else
    doButton(key);
  return (true);
}

void
gauntlet::core::Menu::setOpen(bool open)
{
  isOpen = open;
  if (isOpen)
    {
      cursor = 0;
      draw();
    }
  else
    {
      undraw();
      for (std::vector<Menu *>::iterator it = submenus.begin(); it != submenus.end(); ++it)
	{
	  if ((*it)->getOpen() == true)
	    (*it)->setOpen(false);
	}
    }
}

bool
gauntlet::core::Menu::getOpen()
{
  return (isOpen);
}

void
gauntlet::core::Menu::moveCursor(int newPos)
{
  //TODO move cursor image based on current button position
  cursor = newPos;
}

void
gauntlet::core::Menu::drawButtons()
{
  for (std::vector<MenuButton>::iterator it = buttons.begin(); it != buttons.end(); ++it)
    {
      it->draw();
    }
}

void
gauntlet::core::Menu::undrawButtons()
{
  for (std::vector<MenuButton>::iterator it = buttons.begin(); it != buttons.end(); ++it)
    {
      it->undraw();
    }
}
