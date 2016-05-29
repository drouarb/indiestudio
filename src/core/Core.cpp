#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include "Core.hh"
#include "MainMenu.hh"
#include "Math.hh"
#include "ListenerHandshake.hh"
#include "ListenerStartGame.hh"
#include "ListenerStopSound.hh"
#include "ListenerPlaySound.hh"
#include "ListenerAddParticle.hh"
#include "ListenerDeleteParticle.hh"
#include "ListenerAnimation.hh"
#include "ListenerMap.hh"
#include "PacketFactory.hh"
#include "ConnectMenu.hh"
#include "GameServer.hh"
#include "PlayerController.hh"
#include "CoreUIObserver.hh"
#include "SaveloadMenu.hh"

gauntlet::core::Core::Core() : actionlists(*this), observer(new CoreUIObserver(*this)),
			       menu(*this, MENU_ID_START, NULL), hud(*this, 0, NULL)
{
  listenThread = NULL;
  pc = NULL;
  playing = false;
  serverAddr.first = "";
  serverAddr.second = 0;
  packetf = NULL;
  cpid = -1;
  stoppingPacketf = NULL;
  world::Math::init();

  ogre.setIObserver(observer);
  if (!ogre.init())
    return;
  ogre.playSound(0, (MENU_SOUND), false);
  menu.setOpen(true);

  ogre.go();
}

gauntlet::core::Core::~Core()
{ }

void
gauntlet::core::Core::keyUp(IUIObserver::Key key)
{
  Command cmd = conf.getLinkedKey(key);

  if (pc && gameIsRunning())
    {
      pc->doCmd(cmd, false);
    }
}

void
gauntlet::core::Core::keyDown(IUIObserver::Key key)
{
  lastKey = key;
  Command cmd = conf.getLinkedKey(key);

  if (menu.getOpen())
    {
      menu.keyDown(cmd);
    }
  else
    {
      if (cmd == ESC)
	{
	  menu.setOpen(!menu.getOpen());
	}
      else
	{
	  if (pc && gameIsRunning())
	    pc->doCmd(cmd, true);
	}
    }
}

void
gauntlet::core::Core::buttonClick(int buttonId, struct t_hitItem &item)
{
  if (menu.getOpen())
    {
      menu.buttonClick(buttonId, item);
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
  if (menu.getOpen())
    {
      hud.setOpen(true);
      menu.setOpen(false);
    } 
  actionlists.doActions();
  playing = true;
  ogre.hideBackground(); 
  ogre.stopSound(0);
}

void
gauntlet::core::Core::stop()
{
  if (menu.getOpen() == false)
    {
      ogre.playSound(0, (MENU_SOUND), false);
      menu.setOpen(true);
      hud.setOpen(false);
    }
  playing = false;
  ogre.showBackground();
}

void
gauntlet::core::Core::exit()
{
  ogre.quit();
  if (packetf)
    disconnect("");
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
    usleep(2000000); //TODO: server ready msg?
}

void
gauntlet::core::Core::killServer()
{
  int status = 0;

  if (cpid > 0)
    {
      kill(cpid, SIGTERM);
      waitpid(cpid, &status, 0);
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
	  listeners.push_back(new ListenerStopSound(*this));
	  listeners.push_back(new ListenerPlaySound(*this));
	  listeners.push_back(new ListenerAddParticle(*this));
	  listeners.push_back(new ListenerDeleteParticle(*this));
	  listeners.push_back(new ListenerAnimation(*this));
	  listeners.push_back(new ListenerMap(*this));
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
gauntlet::core::Core::disconnect(std::string const & msg)
{
  destroyPacketf(false);
  if (stoppingPacketf)
    {
      listenThread->join();
      delete listenThread;
      listenThread = NULL;
      delete stoppingPacketf;
      stoppingPacketf = NULL;
    }

  bool sendMsg = !menu.getOpen() && gameIsRunning();
  stop();
  ogre.resetMap();
  if (sendMsg)
    {
      if (msg.length() > 0)
	menu.message(msg);
      else
	menu.message("Disconnected from server.");
    }
  killServer();
}

void
gauntlet::core::Core::destroyPacketf(bool external)
{
  if (disconnectMutex.try_lock() == false)
    return ;
  networkmutex.lock();
  if (packetf)
    {
      if (!external)
	{
	  packetf->stop();
	}
  stoppingPacketf = packetf;
      packetf = NULL;
    }
  disconnectMutex.unlock();
  networkmutex.unlock();
}

void
gauntlet::core::Core::load(std::string const & file)
{
  map = SAVE_DIR + file;
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
