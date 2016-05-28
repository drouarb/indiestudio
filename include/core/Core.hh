//
// core.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:59:47 2016 Esteban Lewis
// Last update Sat May 28 23:34:53 2016 Esteban Lewis
//

#ifndef  CORE_HH_
# define CORE_HH_

# include <mutex>
# include <thread>
# include <unistd.h>
# include "IUIObserver.hh"
# include "Conf.hh"
# include "graph/OgreUI.hh"
# include "ActionLists.hh"
# include "MainMenu.hh"
# include "Hud.hh"

namespace			gauntlet
{
  namespace			network
  {
    class			PacketFactory;
    class			PacketListener;
  };

  namespace			core
  {
    class			PlayerController;

    class			Core
    {
    public:
      Core();
      ~Core();

      void			keyUp(IUIObserver::Key);
      void			keyDown(IUIObserver::Key);
      void			buttonClick(int buttonId, struct t_hitItem & item);
      void			mouseMove(int x, int y);

      void			play();
      void			stop();
      void			exit();
      void			createServer();
      void			initPacketf();
      void			disconnect(std::string const & msg);
      void			destroyPacketf();
      void			load(std::string const & file);
      void			save(std::string const & file);
      bool			gameIsRunning();
      IUIObserver::Key		getLastKey() const;

      OgreUI			ogre;
      Conf			conf;
      PlayerController *	pc;
      std::pair<std::string, int> serverAddr;
      network::PacketFactory *	packetf;
      std::string		map;
      ActionLists		actionlists;
      pid_t			cpid;
      std::mutex		networkmutex;

    private:
      IUIObserver *		observer;
      std::thread *		listenThread;
      MainMenu			menu;
      Hud			hud;
      IUIObserver::Key		lastKey;
      std::list<network::PacketListener*> listeners;
      bool			playing;

      void			killServer();
    };
  };
};

#endif
