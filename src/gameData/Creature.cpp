//
// Created by jonas_e on 5/9/16.
//

#include "Creature.hh"

using namespace gauntlet;

Creature::Creature(bool ncollide, int nid, double posx, double posy,
		   double sizex, double sizey, short norient)
  : Actor(ncollide, nid, posx, posy, sizex, sizey, norient)
{
}

Creature::Creature(int nid, double posx, double posy,
		   double sizex, double sizey, short norient)
  : Actor(nid, posx, posy, sizex, sizey, norient)
{
}
