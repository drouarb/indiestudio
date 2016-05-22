//
// Core.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:13:44 2016 Esteban Lewis
// Last update Mon May 23 00:28:01 2016 Esteban Lewis
//

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Core.hh"
#include "MainMenu.hh"
#include "IUIObserver.hh"
#include "Math.hh"
#include "ListenerAddEntity.hh"
#include "ListenerConnect.hh"
#include "ListenerDisconnect.hh"
#include "ListenerHandshake.hh"
#include "ListenerSelectPlayer.hh"

gauntlet::core::Core::Core() : observer(new CoreUIObserver(*this))
{
  menu = new MainMenu(*this, MENU_ID_START, NULL);
  listenThread = NULL;
  pc = NULL;
  playing = false;
  serverAddr.first = "";
  serverAddr.second = 0;
  packetf = NULL;
  world::Math::init();

  ogre.setIObserver(observer);
  if (!ogre.init())
    return;
  menu->setOpen(true);
  listenThread = new std::thread(&Core::listen, std::ref(*this));
  ogre.go();
  _exit(0);
}

gauntlet::core::Core::~Core()
{ }

void
gauntlet::core::Core::keyUp(IUIObserver::Key key)
{
  Command cmd = conf.getLinkedKey(key);

  if (!menu->getOpen() && cmd != ESC)
    {
      if (pc)
	pc->doCmd(cmd, false);
    }
}

void
gauntlet::core::Core::keyDown(IUIObserver::Key key)
{
  lastKey = key;
  Command cmd = conf.getLinkedKey(key);

  if (menu->getOpen())
    {
      menu->keyDown(cmd);
    }
  else
    {
      if (cmd == ESC)
	{
	  menu->setOpen(!menu->getOpen());
	}
      else
	{
	  if (pc)
	    pc->doCmd(cmd, true);
	}
    }
}

void
gauntlet::core::Core::buttonClick(int buttonId, struct t_hitItem &item)
{
  if (menu->getOpen())
    {
      menu->buttonClick(buttonId, item);
    }
}

void
gauntlet::core::Core::mouseMove(int x, int y)
{
  if (pc)
    {
      x -= ogre.getSizeWindow().first / 2;
      y -= ogre.getSizeWindow().second / 2;
      pc->setAngle(world::Math::getAngle(-atan2(y, x)));
    }
}

void
gauntlet::core::Core::play()
{
  if (menu->getOpen())
    menu->setOpen(false);
  playing = true;
}

void
gauntlet::core::Core::stop()
{
  if (menu->getOpen() == false)
    menu->setOpen(true);
  playing = false;
}

void
gauntlet::core::Core::exit()
{
  ogre.quit();
  
}

void
gauntlet::core::Core::createServer()
{
  //TODO: create server and give map
  std::cout << std::endl << "create server " << map << std::endl << std::endl;
  usleep(100000);
}

void
gauntlet::core::Core::initPacketf()
{
  if (packetf)
    {
      if (listeners.size() == 0)
	{
	  listeners.push_back(new ListenerAddEntity(*this));
	  listeners.push_back(new ListenerConnect(*this));
	  listeners.push_back(new ListenerDisconnect(*this));
	  listeners.push_back(new ListenerHandshake(*this));
	  listeners.push_back(new ListenerSelectPlayer(*this));
	}
      for (std::list<network::PacketListener*>::iterator it = listeners.begin();
	   it != listeners.end(); ++it)
	{
	  packetf->registerListener(*it);
	}
    }
}

void
gauntlet::core::Core::load(std::string file)
{
  map = file;
}

void
gauntlet::core::Core::save(std::string file)
{
  std::cout << "CORE save " << file << std::endl;
}

bool
gauntlet::core::Core::gameIsRunning()
{
  return (playing);
}

gauntlet::core::IUIObserver::Key
gauntlet::core::Core::getLastKey() const
{
  return (lastKey);
}

void
gauntlet::core::Core::listen()
{
  while (1)
    {
      if (packetf)
	packetf->recv();
      else
	usleep(100000);
    }
}
