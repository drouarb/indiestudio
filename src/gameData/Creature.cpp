//
// Created by jonas_e on 5/9/16.
//

#include "Creature.hh"

using namespace gauntlet;

Creature::Creature(int nid, world::World *nworld)
  : Actor(nid, nworld)
{
}

Creature::~Creature()
{
}
