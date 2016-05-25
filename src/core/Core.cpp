#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include "Core.hh"
#include "MainMenu.hh"
#include "IUIObserver.hh"
#include "Math.hh"
#include "ListenerAddEntity.hh"
#include "ListenerDisconnect.hh"
#include "ListenerHandshake.hh"
#include "ListenerMoveEntity.hh"
#include "ListenerStartGame.hh"
#include "ConnectMenu.hh"
#include "GameServer.hh"

gauntlet::core::Core::Core() : observer(new CoreUIObserver(*this)), actionlists(*this)
{
  menu = new MainMenu(*this, MENU_ID_START, NULL);
  listenThread = NULL;
  pc = NULL;
  playing = false;
  serverAddr.first = "";
  serverAddr.second = 0;
  packetf = NULL;
  cpid = -1;
  world::Math::init();

  ogre.setIObserver(observer);
  if (!ogre.init())
    return;
  std::string str = "menu_theme.ogg";
  ogre.loadSound(0, str);
  ogre.playSound(0);
  menu->setOpen(true);

  ogre.go();
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
  actionlists.doActions();
  playing = true;
  ogre.hideBackground();
}

void
gauntlet::core::Core::stop()
{
  if (menu->getOpen() == false)
    menu->setOpen(true);
  playing = false;
  ogre.showBackground();
}

void
gauntlet::core::Core::exit()
{
  ogre.quit();
  if (packetf)
    disconnect(false);
  killServer();
}

void
gauntlet::core::Core::createServer()
{
  killServer();
  cpid = fork();
  if (cpid == -1)
    return ;
  if (cpid == 0)
    {
      world::GameServer(map, serverAddr.second);
      _exit(0);
    }
  else
    usleep(1000000); //TODO: server ready msg?
}

void
gauntlet::core::Core::killServer()
{
  int status = 0;

  if (cpid > 0)
    {
      kill(cpid, SIGTERM);
      waitpid(cpid, &status, WNOHANG);
      cpid = -1;
    }
}

void
gauntlet::core::Core::initPacketf()
{
  if (packetf)
    {
      if (listeners.size() == 0)
	{
	  listeners.push_back(new ListenerAddEntity(*this));
	  listeners.push_back(new ListenerDisconnect(*this));
	  listeners.push_back(new ListenerHandshake(*this));
	  listeners.push_back(new ListenerMoveEntity(*this));
	  listeners.push_back(new ListenerStartGame(*this));
	}
      for (std::list<network::PacketListener*>::iterator it = listeners.begin();
	   it != listeners.end(); ++it)
	{
	  packetf->registerListener(*it);
	}
      listenThread = new std::thread(&network::PacketFactory::recv, std::ref(*packetf));
    }
}

void
gauntlet::core::Core::disconnect(bool send)
{
  network::PacketDisconnect pd("");

  if (packetf)
    {
      if (send)
	packetf->send((network::Packet&)pd);
      packetf->stop();
      delete packetf;

      listenThread->join();
      delete listenThread;
      listenThread = NULL;

      packetf = NULL;
      stop();
    }
  killServer();
}

void
gauntlet::core::Core::load(std::string const & file)
{
  map = SAVE_DIR + file;
}

void
gauntlet::core::Core::save(std::string const & file)
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
