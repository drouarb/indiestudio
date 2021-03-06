//
// core.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
//
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
//
// Started on  Mon May  9 10:59:47 2016 Esteban Lewis
// Last update Sun Jun  5 17:27:19 2016 Benjamin DROUARD
//

#ifndef  CORE_HH_
# define CORE_HH_

# include <mutex>
# include <thread>
# include "IUIObserver.hh"
# include "Conf.hh"
# include "graph/OgreUI.hh"
# include "ActionLists.hh"
# include "MainMenu.hh"
# include "Hud.hh"

#ifdef _WIN32
# define pid_t int
#else
# include <unistd.h>
#endif

namespace gauntlet
{
    namespace network
    {
        class PacketFactory;

        class PacketListener;
    };

    namespace core
    {
        class PlayerController;

        class Core
        {
        public:
            Core();

            ~Core();

            void keyUp(IUIObserver::Key);
            void keyDown(IUIObserver::Key);
            void buttonClick(int buttonId, struct t_hitItem &item);
            void mouseMove(int x, int y);
            void tick();

            void play();
            void stop();
            void exit();
            void createServer();
            void initPacketf();
            void disconnect(std::string const &msg);
            void destroyPacketf();
            void load(std::string const &file);
            bool gameIsRunning();
            IUIObserver::Key getLastKey() const;

            OgreUI ogre;
            Conf conf;
            PlayerController *pc;
            std::pair<std::string, int> serverAddr;
            network::PacketFactory *packetf;
            std::string map;
            ActionLists actionlists;
            pid_t cpid;
            std::mutex networkmutex;
            Hud hud;

        private:
            IUIObserver *observer;
            std::thread *listenThread;
            MainMenu menu;
            IUIObserver::Key lastKey;
            std::list<network::PacketListener *> listeners;
            bool playing;
            std::mutex disconnectMutex;
            network::PacketFactory *stoppingPacketf;

#ifdef _WIN32
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
#endif

            void killServer();
        };
    };
};

#endif
