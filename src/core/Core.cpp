//
// Core.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 11:13:44 2016 Esteban Lewis
// Last update Sat May 14 14:18:23 2016 Esteban Lewis
//

#include <iostream>
#include "Math.hh"
#include "Core.hh"
#include "MainMenu.hh"

gauntlet::core::Core::Core() : keepGoing(true)
{
  menu = new MainMenu(*this, 100);

  std::cout << std::endl << "-- TEST menu saveload 1st load" << std::endl;
  keyDown(IUIObserver::KEY_ESC);
  keyDown(IUIObserver::KEY_DOWN);
  std::cout << "--TEST saveload" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  std::cout << "--TEST select" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);
  keyDown(IUIObserver::KEY_UP);
  std::cout << "--TEST load" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);

  std::cout << std::endl << "-- TEST menu conf enter esc" << std::endl;
  keyDown(IUIObserver::KEY_ESC);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  std::cout << "-- TEST settings" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  keyDown(IUIObserver::KEY_DOWN);
  std::cout << "-- TEST validate" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);
  std::cout << "-- TEST escape" << std::endl;
  keyDown(IUIObserver::KEY_ESC);
  std::cout << "-- TEST exit" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);
  std::cout << "-- TEST exit" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);

  std::cout << std::endl << "-- TEST menu play" << std::endl;
  keyDown(IUIObserver::KEY_ENTER);
  keyDown(IUIObserver::KEY_ESC);

  //loop();
}

gauntlet::core::Core::~Core()
{
  delete menu;
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
	  pc.doCmd(cmd, true);
	}
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

gauntlet::core::IUIObserver::Key
gauntlet::core::Core::getLastKey()
{
  return (lastKey);
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
