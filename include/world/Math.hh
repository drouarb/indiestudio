//
// Math.hh for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Sat May 14 13:43:42 2016 Esteban Lewis
// Last update Sun May 22 17:07:10 2016 Esteban Lewis
//

#ifndef  GAUNTLET_MATH_HH_
# define GAUNTLET_MATH_HH_

#include <map>

namespace			gauntlet
{
  namespace			world
  {
    class			Math
    {
    public:
      static void		init();
      static short		getAngle(double rad);
      static double		cos(short angle);
      static double		sin(short angle);
      static bool		isBetween(short ref, short angle_sup, short angle_inf);
      static double		distBetween(std::pair<double, double> pos1, std::pair<double, double> pos2);
      static float		toRad(short angle);

      //no need to simplify before calling other methods
      static short		simplify(short angle); 

      enum			NotableAngles
	{
	  A_NULL = 0,
	  A_RIGHT = 157,
	  A_FLAT = 314,
	  A_RIGHT_NEG = 471,
	  A_FULL = 628
	};
    };
  };
};

#endif
