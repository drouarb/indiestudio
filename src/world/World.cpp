//
// World.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:58:51 2016 Esteban Lewis
// Last update Sat May 14 14:19:06 2016 Esteban Lewis
//

#include <iostream>
#include "World.hh"
#include "Math.hh"

gauntlet::world::World::World()
{
  Math::init();
}

gauntlet::world::World::~World()
{ }

void
gauntlet::world::World::update()
{
  std::cout << "WORLD update" << std::endl;
}

void
gauntlet::world::World::loadGame(std::string file)
{
  std::cout << "WORLD load " << file << std::endl;
}
