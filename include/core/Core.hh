//
// core.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:59:47 2016 Esteban Lewis
// Last update Fri May 20 23:24:10 2016 Esteban Lewis
//

#ifndef  CORE_HH_
# define CORE_HH_

# include <thread>
# include <mutex>
# include <unistd.h>
# include "CoreUIObserver.hh"
# include "Menu.hh"
# include "PlayerController.hh"
# include "Stopwatch.hh"
# include "Conf.hh"
# include "ConfMenu.hh"
# include "Position.hh"
# include "OgreUI.hh"
# include "Thread.hpp"

namespace			gauntlet
{
  namespace			core
  {
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
      void			exit();
      void			load(std::string file);
      void			save(std::string file);
      Conf &			getConf();
      OgreUI &			getGui();

    private:
      bool			keepGoing;
      IUIObserver *		observer;
      OgreUI			ogre;
      std::mutex		ogreMutex;
      Thread<void (Core::*)(void *), Core> * loopThread;
      Menu *			menu;
      PlayerController		pc;
      Stopwatch			sw;
      Conf			conf;
      IUIObserver::Key		lastKey;

      void			loop(void *);
      void			updateWorld();
    };
  };
};

#endif
