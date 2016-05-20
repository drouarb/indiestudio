//
// Math.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Sat May 14 13:48:47 2016 Esteban Lewis
// Last update Fri May 20 14:11:13 2016 Alexis Trouve
//

#include <math.h>
#include "Math.hh"

static double cos_tab[629];
static double sin_tab[629];

void
gauntlet::world::Math::init()
{
  for (int a = 0; a <= 628; ++a)
    {
      cos_tab[a] = ::cos((double)a / 100);
      sin_tab[a] = ::sin((double)a / 100);
    }
}

short
gauntlet::world::Math::getAngle(double rad)
{
  return (simplify((int)(rad * 100)));
}

double
gauntlet::world::Math::cos(short angle)
{
  return (cos_tab[simplify(angle)]);
}

double
gauntlet::world::Math::sin(short angle)
{
  return (sin_tab[simplify(angle + A_FLAT)]);
}

short
gauntlet::world::Math::simplify(short angle)
{
  angle = angle % 629;
  if (angle < 0)
    angle += 628;
  return (angle);
}

bool
gauntlet::world::Math::isBetween(short ref, short sup, short inf)
{
  ref = simplify(ref);
  sup = simplify(sup);
  inf = simplify(inf);
  if (inf > sup)
    sup += 628;
  if (ref < inf)
    ref += 628;
  return (ref >= inf && ref <= sup);
}
