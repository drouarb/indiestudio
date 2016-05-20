//
// Core.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:13:44 2016 Esteban Lewis
// Last update Fri May 20 17:08:24 2016 Esteban Lewis
//

#include <iostream>
#include "Core.hh"
#include "MainMenu.hh"

gauntlet::core::Core::Core() : keepGoing(true), observer(new CoreUIObserver(*this))
{
  menu = new MainMenu(*this, 100, NULL);
  menu->setOpen(true);

  ogre.setIObserver(observer);
  std::mutex m;
  m.lock();
  ogreThread = new std::thread(&OgreUI::go, ogre, std::ref(m));
  m.lock();
  ogre.addButton(PLEFT, 145, "Hello", 0);

  loop();
}

gauntlet::core::Core::~Core()
{
  delete menu;
  ogre.quit();
  ogreThread->join();
  delete ogreThread;
}

void
gauntlet::core::Core::keyUp(IUIObserver::Key key)
{
  Command cmd = conf.getLinkedKey(key);

  if (!menu->getOpen() && cmd != ESC)
    {
      pc.doCmd(cmd, false);
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
	  pc.doCmd(cmd, true);
	}
    }
}

void
gauntlet::core::Core::buttonClick(int buttonId, struct t_hitItem & item)
{
  (void)item;
  std::cout << "CORE button clicked " << buttonId << std::endl;
  if (menu->getOpen())
    {
      menu->buttonClick(buttonId);
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
  //if no server
  //	if player
  //		destroy player
  //	create server
  //if no player
  //	open lobby and create player
  //close menu and display
}

void
gauntlet::core::Core::exit()
{
  std::cout << "CORE exit" << std::endl;
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

gauntlet::core::Conf &
gauntlet::core::Core::getConf()
{
  return (conf);
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
  std::cout << "CORE update world" << std::endl;
  //...
  pc.loop();
}
