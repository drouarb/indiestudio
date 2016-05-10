//
// MenuButton.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:47:34 2016 Esteban Lewis
// Last update Tue May 10 10:55:39 2016 Esteban Lewis
//

#include <iostream>
#include "MenuButton.hh"

gauntlet::core::MenuButton::MenuButton(std::string const & str, int x, int y,
				       int id/*, OgreUI & ogre*/) :
  x(x), y(y), str(str), id(id)//, ogre(ogre)
{ }

gauntlet::core::MenuButton::MenuButton(gauntlet::core::MenuButton const & other) :
  x(other.x), y(other.y), str(other.str), id(other.id)//, ogre(other.ogre)
{ }

gauntlet::core::MenuButton::~MenuButton()
{ }

gauntlet::core::MenuButton &
gauntlet::core::MenuButton::operator=(MenuButton const & other)
{
  x = other.x;
  y = other.y;
  str = other.str;
  id = other.id;
  //ogre = other.ogre;
  return (*this);
}

int
gauntlet::core::MenuButton::getX()
{
  return (x);
}

int
gauntlet::core::MenuButton::getY()
{
  return (y);
}

std::string const &
gauntlet::core::MenuButton::getStr()
{
  return (str);
}

void
gauntlet::core::MenuButton::draw(/*OgreUI &*/)
{
  //OgreUI.addText(x, y, id);
  std::cout << "BTNADD " << id << " " << str << std::endl;
}

void
gauntlet::core::MenuButton::undraw(/*OgreUI &*/)
{
  //OgreUI.removeText(id);
  std::cout << "BTNRMV " << id << " " << str << std::endl;
}
