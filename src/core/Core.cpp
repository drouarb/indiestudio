//
// Core.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:13:44 2016 Esteban Lewis
// Last update Sat May 21 18:01:54 2016 Esteban Lewis
//

#include <iostream>
#include "Core.hh"
#include "MainMenu.hh"

gauntlet::core::Core::Core() : keepGoing(true), observer(new CoreUIObserver(*this))
{
  menu = new MainMenu(*this, MENU_ID_START, NULL);
  ogreThread = NULL;
  pc = NULL;

  ogre.setIObserver(observer);
  if (!ogre.init())
    return ;
  menu->setOpen(true);
  ogreThread = new std::thread(&OgreUI::go, std::ref(ogre));
  loop();
}

gauntlet::core::Core::~Core()
{
  if (ogreThread)
    {
      ogreThread->join();
      delete ogreThread;
    }
  delete menu;
}

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
gauntlet::core::Core::buttonClick(int buttonId, struct t_hitItem & item)
{
  if (menu->getOpen())
    {
      menu->buttonClick(buttonId, item);
    }
}

void
gauntlet::core::Core::mouseMove(int x, int y)
{
  (void)x;
  (void)y;
  //TODO: update player rotation
}

void
gauntlet::core::Core::play()
{
  std::cout << "CORE play" << std::endl;
}

void
gauntlet::core::Core::exit()
{
  ogre.quit();
  keepGoing = false;
}

void
gauntlet::core::Core::load(std::string file)
{
  std::cout << "CORE load " << file << std::endl;
}

void
gauntlet::core::Core::save(std::string file)
{
  std::cout << "CORE save " << file << std::endl;
}

bool
gauntlet::core::Core::gameIsRunning()
{
  return (false);
}

void
gauntlet::core::Core::loop()
{
  long ms;

  while (keepGoing)
    {
      sw.Set();
      if (menu->getOpen() == false)
	{
	  updateWorld();
	}
      ms = sw.EllapsedMs();
      if (ms < 17)
	usleep(17 - sw.EllapsedMs()); //TODO: 60 fps okay?
    }
}

void
gauntlet::core::Core::updateWorld()
{
  //...
  if (pc)
    pc->loop();
}
