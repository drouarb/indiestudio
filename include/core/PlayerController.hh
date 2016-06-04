//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:49:54 2016 Esteban Lewis
// Last update Wed May 25 23:19:12 2016 Esteban Lewis
//

#ifndef  PLAYERCONTROLLER_HH_
# define PLAYERCONTROLLER_HH_

# include <vector>
# include <map>
# include <Stopwatch.hh>
# include "Conf.hh"
# include "PlayerChars.hh"

namespace gauntlet
{
    namespace core
    {
        class Core;

        class PlayerController
        {
        public:
            PlayerController(std::string const &name, world::PlayerChar, Core &);
            ~PlayerController();

            std::string const &getName() const;
            world::PlayerChar getChar() const;
            void doCmd(Command, bool down);
            void setAngle(short);

        private:
            Core &core;
            std::vector<Command> ctrls;
            std::map<Command, Command> stopCmds;
            world::PlayerChar chartype;
            short angle;
            std::string name;
            Stopwatch sw;
        };
    };
};

#endif
