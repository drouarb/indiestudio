//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:52:38 2016 Esteban Lewis
// Last update Wed May 25 23:48:48 2016 Esteban Lewis
//

#include <iostream>
#include "PlayerController.hh"
#include "PacketControl.hh"
#include "Core.hh"

gauntlet::core::PlayerController::PlayerController(std::string const & name,
						   world::PlayerChar c,
						   Core & core) : core(core)
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

  stopCmds.insert(std::pair<Command, Command>(UP, UP_STOP));
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
  if (!down)
    {
      bool ok = false;
      for (std::map<Command, Command>::iterator it = stopCmds.begin();
	   it != stopCmds.end(); ++it)
	{
	  if (it->first == key)
	    {
	      ok = true;
	      key = it->second;
	      break ;
	    }
	}
      if (!ok)
	return ;
    }

  for (std::vector<Command>::iterator it = ctrls.begin(); it != ctrls.end(); ++it)
    {
      if (*it == key)
	{
	  core.packetf->send(network::PacketControl((unsigned char)key, angle));
	  return ;
	}
    }
}
