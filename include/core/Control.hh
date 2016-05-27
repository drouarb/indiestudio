//
// Control.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 13:37:58 2016 Esteban Lewis
// Last update Thu May 26 15:34:00 2016 Esteban Lewis
//

#ifndef  CONTROL_HH_
# define CONTROL_HH_

# include <map>
# include <string>
# include "Position.hh"
# include "graph/OgreUI.hh"

namespace			gauntlet
{
  namespace			core
  {
    class			Control
    {
    public:
      Control(MenuItemType, std::string const & str, void * param, Position p,
	      int id, OgreUI &);
      Control(Control const &);
      ~Control();

      Control &			operator=(Control const &);

      Position			getPos() const;
      const std::string &	getStr() const;
      void			setStr(const std::string &);
      const void *		getParam() const;
      void			setParam(void *);
      void			draw();
      void			undraw();
      void			update(struct t_hitItem &);
      int			getId();

      typedef void (Control::*CtrlFun)();

    private:
      MenuItemType		type;
      Position			pos;
      std::string		str;
      void *			param;
      int			id;
      OgreUI &			ogre;
      bool			displayed;
      CtrlFun			createFun;

      void			makeButton();
      void			makeSlidebar();
      void			makeCheckbox();
      void			makeTextbox();
      void			makeLabel();
      void			makeSelectmenu();
      void			makeProgressbar();
    };
  };
};

#endif
