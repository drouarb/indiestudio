//
// Core.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:13:44 2016 Esteban Lewis
// Last update Mon May  9 11:20:42 2016 Esteban Lewis
//

#include <iostream>
#include "Core.hh"

gauntlet::core::Core::Core()
{
  std::cout << "Core initialized." << std::endl;
  keyUp(IUIObserver::KEY_UP);
  keyDown(IUIObserver::KEY_UP);
}

gauntlet::core::Core::~Core()
{ }

void
gauntlet::core::Core::keyUp(IUIObserver::Key key)
{
  std::cout << "Key up: " << key << std::endl;
}

void
gauntlet::core::Core::keyDown(IUIObserver::Key key)
{
  std::cout << "Key down: " << key << std::endl;
}
