//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:52:38 2016 Esteban Lewis
// Last update Wed May 25 19:52:56 2016 Esteban Lewis
//

#include <iostream>
#include "PlayerController.hh"

gauntlet::core::PlayerController::PlayerController(std::string const & name,
						   world::PlayerChar c)
{
  this->name = name;
  chartype = c;

  ctrls =
    {
      UP,
      ATTACK1,
      ATTACK2,
      ATTACK3,
      ATTACK4
    };
}

gauntlet::core::PlayerController::~PlayerController()
{ }

std::string const &
gauntlet::core::PlayerController::getName() const
{
  return (name);
}

gauntlet::world::PlayerChar
gauntlet::core::PlayerController::getChar() const
{
  return (chartype);
}

void
gauntlet::core::PlayerController::setAngle(short newangle)
{
  angle = newangle;
}

void
gauntlet::core::PlayerController::doCmd(Command key, bool down)
{
  for (std::vector<Command>::iterator it = ctrls.begin(); it != ctrls.end(); ++it)
    {
      if (*it == key)
	{
	  std::cout << "player cmd " << key << " " << down << std::endl;
	  //TODO: send command packet with angle
	  return ;
	}
    }
}
