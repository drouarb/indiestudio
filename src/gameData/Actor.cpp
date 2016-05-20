//
// Created by jonas_e on 5/9/16.
//

#include <iostream>
#include "Actor.hh"

using namespace gauntlet;

Actor::Actor(bool ncollide, int nid, double posx, double posy,
	     double sizex, double sizey, short norient)
  : ABody(ncollide, nid, posx, posy, sizex, sizey, norient)
{
}

Actor::Actor(int nid, double posx, double posy,
	     double sizex, double sizey, short norient)
  : ABody(nid, posx, posy, sizex, sizey, norient)
{
}

Actor::~Actor()
{
}
