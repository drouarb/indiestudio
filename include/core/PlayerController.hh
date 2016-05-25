//
// PlayerController.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 15:49:54 2016 Esteban Lewis
// Last update Wed May 25 19:46:03 2016 Esteban Lewis
//

#ifndef  PLAYERCONTROLLER_HH_
# define PLAYERCONTROLLER_HH_

# include <vector>
# include "Conf.hh"
# include "PlayerChars.hh"

namespace				gauntlet
{
  namespace				core
  {
    class				PlayerController
    {
    public:
      PlayerController(std::string const & name, world::PlayerChar);
      ~PlayerController();

      std::string const &		getName() const;
      world::PlayerChar			getChar() const;

      void				doCmd(Command, bool down);
      void				setAngle(short);

    private:
      std::vector<Command>		ctrls;
      world::PlayerChar			chartype;
      std::string			name;
    };
  };
};

#endif
