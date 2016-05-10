//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:52:38 2016 Esteban Lewis
// Last update Mon May  9 17:44:18 2016 Esteban Lewis
//

#include <iostream>
#include "PlayerController.hh"

gauntlet::core::PlayerController::PlayerController()
{
  ctrls.insert(std::pair<IUIObserver::Key, void (PlayerController::*)(bool)>
	       (IUIObserver::KEY_UP, &PlayerController::cmdUp));
  ctrls.insert(std::pair<IUIObserver::Key, void (PlayerController::*)(bool)>
	       (IUIObserver::KEY_DOWN, &PlayerController::cmdDown));
  ctrls.insert(std::pair<IUIObserver::Key, void (PlayerController::*)(bool)>
	       (IUIObserver::KEY_LEFT, &PlayerController::cmdLeft));
  ctrls.insert(std::pair<IUIObserver::Key, void (PlayerController::*)(bool)>
	       (IUIObserver::KEY_RIGHT, &PlayerController::cmdRight));
  ctrls.insert(std::pair<IUIObserver::Key, void (PlayerController::*)(bool)>
	       (IUIObserver::KEY_ENTER, &PlayerController::cmdAttack1));

  moveX = 0;
  moveY = 0;
  action = NONE;
}

gauntlet::core::PlayerController::~PlayerController()
{ }

void
gauntlet::core::PlayerController::loop()
{
  action = NONE;
}

void
gauntlet::core::PlayerController::doCmd(IUIObserver::Key key, bool down)
{
  std::cout << "player cmd " << key << " " << down << std::endl;
  for (std::map<IUIObserver::Key, void (PlayerController::*)(bool)>::iterator
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
