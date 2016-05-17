//
// MenuButton.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:37:58 2016 Esteban Lewis
// Last update Tue May 17 15:15:26 2016 Esteban Lewis
//

#ifndef  MENUBUTTON_HH_
# define MENUBUTTON_HH_

# include <string>
# include "Position.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			MenuButton
    {
    public:
      MenuButton(std::string const & str, Position p, int id/*, OgreUI &*/);
      MenuButton(MenuButton const &);
      ~MenuButton();

      MenuButton &		operator=(MenuButton const &);

      Position			getPos();
      std::string const &	getStr();
      void			draw();
      void			undraw();
      int			getId();

    private:
      Position			pos;
      std::string		str;
      int			id;
      //OgreUI &		ogre; //TODO
    };
  };
};

#endif
