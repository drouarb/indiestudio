//
// Control.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:47:34 2016 Esteban Lewis
// Last update Sat May 21 11:35:17 2016 Esteban Lewis
//

#include <iostream>
#include <stdexcept>
#include "Control.hh"

gauntlet::core::Control::Control(MenuItemType type, std::string const & str, void * param,
				 Position p, int id, OgreUI & ogre) :
  type(type), pos(p), str(str), param(param), id(id), ogre(ogre), displayed(false)
{
  switch (type)
    {
    case BUTTON:
      createFun = &Control::makeButton;
      break;
    case SLIDE:
      createFun = &Control::makeSlidebar;
      break;
    case CHECKBOX:
      createFun = &Control::makeCheckbox;
      break;
    case TEXTBOX:
      createFun = &Control::makeTextbox;
      break;
    case LABEL:
      createFun = &Control::makeLabel;
      break;
    case SELECTMENU:
      createFun = &Control::makeSelectmenu;
      break;
    case PROGRESSBAR:
      createFun = &Control::makeProgressbar;
      break;
    default:
      throw std::invalid_argument("Control type");
    }
}

gauntlet::core::Control::Control(gauntlet::core::Control const & other) :
  type(other.type), pos(other.pos), str(other.str), param(other.param), id(other.id),
  ogre(other.ogre), displayed(other.displayed), createFun(other.createFun)
{
  undraw();
}

gauntlet::core::Control::~Control()
{ }

gauntlet::core::Control &
gauntlet::core::Control::operator=(Control const & other)
{
  type = other.type;
  pos = other.pos;
  str = other.str;
  param = other.param;
  id = other.id;
  displayed = other.displayed;
  createFun = other.createFun;
  return (*this);
}

gauntlet::core::Position
gauntlet::core::Control::getPos() const
{
  return (pos);
}

std::string const &
gauntlet::core::Control::getStr() const
{
  return (str);
}

const void *
gauntlet::core::Control::getParam() const
{
  return (param);
}

void
gauntlet::core::Control::setParam(void * newval)
{
  param = newval;
}

void
gauntlet::core::Control::draw()
{
  if (!displayed)
    {
      (this->*createFun)();
      displayed = true;
    }
}

void
gauntlet::core::Control::undraw()
{
  if (displayed)
    {
      ogre.remove(id);
      displayed = false;
    }
}

int
gauntlet::core::Control::getId()
{
  return (id);
}



void
gauntlet::core::Control::makeButton()
{
  ogre.addButton(pos, id, str, 0);
}

void
gauntlet::core::Control::makeSlidebar()
{
  ogre.addSlideBar(pos, id, str, *(int*)param, 0);
}

void
gauntlet::core::Control::makeCheckbox()
{
  ogre.addCheckbox(pos, id, str, 0);
}

void
gauntlet::core::Control::makeTextbox()
{
  ogre.addTextbox(pos, id, str, 0);
}

void
gauntlet::core::Control::makeLabel()
{
  ogre.addLabel(pos, id, str, 0);
}

void
gauntlet::core::Control::makeSelectmenu()
{
  ogre.addSelectMenu(pos, id, str, *(std::vector<std::string>*)param, 0);
}

void
gauntlet::core::Control::makeProgressbar()
{
  ogre.addProgressBar(pos, id, str, 0, *(int*)param);
}
