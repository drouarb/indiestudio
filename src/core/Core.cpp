#include <math.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/wait.h>
#endif
#include "Core.hh"
#include "Math.hh"
#include "ListenerHandshake.hh"
#include "ListenerStartGame.hh"
#include "PacketFactory.hh"
#include "GameServer.hh"
#include "PlayerController.hh"
#include "CoreUIObserver.hh"
#include "LoadMenu.hh"

gauntlet::core::Core::Core() : actionlists(*this), hud(*this, 0, NULL),
                               observer(new CoreUIObserver(*this)),
                               menu(*this, MENU_ID_START, NULL)
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
    ogre.playSound(0, (MENU_SOUND), true);
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
    if (pc && menu.getOpen() == false)
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
    if (playing)
        {
            ogre.playSound(0, (MENU_SOUND), true);
            if (menu.getOpen() == false)
                menu.setOpen(true);
            if (hud.getOpen() == true)
                hud.setOpen(false);
        }
    playing = false;
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
        return;
	if (cpid == 0)
	{
		world::GameServer(map, serverAddr.second);
		_exit(0);
	}
	else
#ifdef _WIN32
		Sleep(4000);
#else
        usleep(4000000); //TODO: server ready msg?
#endif
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
                    listeners.push_back(new ListenerHUD(*this));
                    listeners.push_back(new ListenerDeleteEntity(*this));
                }
            for (std::list<network::PacketListener *>::iterator it = listeners.begin();
                 it != listeners.end(); ++it)
                {
                    packetf->registerListener(*it);
                }
            listenThread = new std::thread(std::bind(&network::PacketFactory::recv, std::ref(*packetf)));
        }
}

void
gauntlet::core::Core::disconnect(std::string const &msg)
{
    std::cout << "# disconnect a" << std::endl;
    destroyPacketf(false);
    std::cout << "# disconnect b" << std::endl;
    if (stoppingPacketf)
        {
            std::cout << "# disconnect c" << std::endl;
            listenThread->join();
            std::cout << "# disconnect d" << std::endl;
            delete listenThread;
            listenThread = NULL;
            delete stoppingPacketf;
            stoppingPacketf = NULL;
            std::cout << "# disconnect e" << std::endl;
        }

    std::cout << "# disconnect f" << std::endl;
    bool sendMsg = !menu.getOpen() && gameIsRunning();
    std::cout << "# disconnect g" << std::endl;
    ogre.resetMap();
    std::cout << "# disconnect h" << std::endl;
    stop();
    std::cout << "# disconnect i" << std::endl;
    if (sendMsg)
        {
            std::cout << "# disconnect j" << std::endl;
            if (msg.length() > 0)
                menu.message(msg);
            else
                menu.message("Disconnected from server.");
            std::cout << "# disconnect k" << std::endl;
        }
    std::cout << "# disconnect l" << std::endl;
    killServer();
    std::cout << "# disconnect m" << std::endl;
}

void
gauntlet::core::Core::destroyPacketf(bool external)
{
    std::cout << "# destroyPacketf a" << std::endl;
    if (disconnectMutex.try_lock() == false)
        return;
    std::cout << "# destroyPacketf b" << std::endl;
    networkmutex.lock();
    std::cout << "# destroyPacketf c" << std::endl;
    if (packetf)
        {
            std::cout << "# destroyPacketf d" << std::endl;
            if (!external)
                {
                    std::cout << "# destroyPacketf e" << std::endl;
                    packetf->stop();
                    std::cout << "# destroyPacketf f" << std::endl;
                }
            std::cout << "# destroyPacketf g" << std::endl;
            stoppingPacketf = packetf;
            packetf = NULL;
            std::cout << "# destroyPacketf h" << std::endl;
        }
    disconnectMutex.unlock();
    networkmutex.unlock();
    std::cout << "# destroyPacketf i" << std::endl;
}

void
gauntlet::core::Core::load(std::string const &file)
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

void gauntlet::core::Core::tick()
{
    if (menu.getOpen())
        menu.tick();
    if (hud.getOpen())
       hud.tick();
}


