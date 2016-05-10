//
// World.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:55:06 2016 Esteban Lewis
// Last update Mon May  9 15:03:38 2016 Esteban Lewis
//

#ifndef  WORLD_HH_
# define WORLD_HH_

# include <string>

namespace			gauntlet
{
  namespace			world
  {
    class			World
    {
    public:
      World();
      ~World();

      void			update();
      void			loadGame(std::string file);
    };
  };
};

#endif
