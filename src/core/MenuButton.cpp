//
// MenuButton.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:47:34 2016 Esteban Lewis
// Last update Tue May 17 15:15:58 2016 Esteban Lewis
//

#include <iostream>
#include "MenuButton.hh"

gauntlet::core::MenuButton::MenuButton(std::string const & str, Position p,
				       int id/*, OgreUI & ogre*/) :
  pos(p), str(str), id(id)//, ogre(ogre)
{ }

gauntlet::core::MenuButton::MenuButton(gauntlet::core::MenuButton const & other) :
  pos(other.pos), str(other.str), id(other.id)//, ogre(other.ogre)
{
  //remove from 
}

gauntlet::core::MenuButton::~MenuButton()
{ }

gauntlet::core::MenuButton &
gauntlet::core::MenuButton::operator=(MenuButton const & other)
{
  pos = other.pos;
  str = other.str;
  id = other.id;
  //ogre = other.ogre;
  return (*this);
}

gauntlet::core::Position
gauntlet::core::MenuButton::getPos()
{
  return (pos);
}

std::string const &
gauntlet::core::MenuButton::getStr()
{
  return (str);
}

void
gauntlet::core::MenuButton::draw()
{
  //ogre.addButton(pos, id, text, 0);
  std::cout << "BTNADD " << id << " " << str << std::endl;
}

void
gauntlet::core::MenuButton::undraw()
{
  //ogre.removeButton(id);
  std::cout << "BTNRMV " << id << " " << str << std::endl;
}

int
gauntlet::core::MenuButton::getId()
{
  return (id);
}
