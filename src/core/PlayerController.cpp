//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:52:38 2016 Esteban Lewis
// Last update Tue May 24 12:52:46 2016 Esteban Lewis
//

#include <iostream>
#include "PlayerController.hh"

gauntlet::core::PlayerController::PlayerController(std::string const & name,
						   world::PlayerChar c)
{
  id = -1;
  this->name = name;
  chartype = c;

  ctrls.insert(std::pair<Command, void (PlayerController::*)(bool)>
	       (UP, &PlayerController::cmdUp));
  ctrls.insert(std::pair<Command, void (PlayerController::*)(bool)>
	       (DOWN, &PlayerController::cmdDown));
  ctrls.insert(std::pair<Command, void (PlayerController::*)(bool)>
	       (LEFT, &PlayerController::cmdLeft));
  ctrls.insert(std::pair<Command, void (PlayerController::*)(bool)>
	       (RIGHT, &PlayerController::cmdRight));
  ctrls.insert(std::pair<Command, void (PlayerController::*)(bool)>
	       (ENTER, &PlayerController::cmdAttack1));

  moveX = 0;
  moveY = 0;
  action = NONE;
  playerRef = NULL;
}

gauntlet::core::PlayerController::~PlayerController()
{ }

std::string const &
gauntlet::core::PlayerController::getName() const
{
  return (name);
}

std::pair<double, double>
gauntlet::core::PlayerController::getMovement()
{
  return (std::pair<double, double>(moveX, moveY));
}

int
gauntlet::core::PlayerController::getAction()
{
  return (action);
}

void
gauntlet::core::PlayerController::setAngle(short angle)
{
  (void)angle;
}

void
gauntlet::core::PlayerController::loop()
{
  action = NONE;
}

void
gauntlet::core::PlayerController::doCmd(Command key, bool down)
{
  std::cout << "player cmd " << key << " " << down << std::endl;
  for (std::map<Command, void (PlayerController::*)(bool)>::iterator
	 it = ctrls.begin(); it != ctrls.end(); ++it)
    {
      if (it->first == key)
	{
	  (this->*(it->second))(down);
	  return ;
	}
    }
}

void
gauntlet::core::PlayerController::cmdUp(bool down)
{
  if (down)
    {
      moveY = (moveY != 0 ? -0.707 : -1);
    }
  else
    {
      moveY = 0;
    }
}

void
gauntlet::core::PlayerController::cmdDown(bool down)
{
  if (down)
    {
      moveY = (moveY != 0 ? 0.707 : 1);
    }
  else
    {
      moveY = 0;
    }
}

void
gauntlet::core::PlayerController::cmdLeft(bool down)
{
  if (down)
    {
      moveX = (moveX != 0 ? -0.707 : -1);
    }
  else
    {
      moveX = 0;
    }
}

void
gauntlet::core::PlayerController::cmdRight(bool down)
{
  if (down)
    {
      moveX = (moveX != 0 ? 0.707 : 1);
    }
  else
    {
      moveX = 0;
    }
}

void
gauntlet::core::PlayerController::cmdAttack1(bool down)
{
  if (down)
    {
      action = ATTACK1;
    }
}
