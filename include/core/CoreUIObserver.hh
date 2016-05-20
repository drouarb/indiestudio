//
// EventHandler.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 10:52:22 2016 Esteban Lewis
// Last update Tue May 17 15:27:51 2016 Esteban Lewis
//

#ifndef  COREUIOBSERVER_HH_
# define COREUIOBSERVER_HH_

# include "IUIObserver.hh"

namespace gauntlet {
    namespace core {
        class Core;

        class CoreUIObserver : public IUIObserver {
        public:
            CoreUIObserver(Core &);

            ~CoreUIObserver();

            void keyDown(Key k);

            void keyUp(Key k);

            void mouseMove(int x, int y);

            void itemClick(int buttonId, struct t_hitItem item);

        private:
            Core &core;
        };
    };
};

#endif
