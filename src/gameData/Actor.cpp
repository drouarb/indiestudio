//
// Created by jonas_e on 5/9/16.
//

#include <iostream>
#include "Actor.hh"
#include "World.hh"
#include "Spell.hh"

using namespace gauntlet;

Actor::Actor(int nid, world::World *nworld)
  : ABody(nid)
{
  world = nworld;
}

Actor::~Actor()
{
}

void		Actor::move()
{
  world->getCollider().applyVectorToId(id, orientation, stats.speed);
}

ABody		*Actor::clone(int id) const
{
  Actor		*actor;
  unsigned int	i;

  actor = new Actor(id, world);
  actor->setName(name);
  actor->stats.HP = stats.HP;
  actor->stats.normalHP = stats.normalHP;
  actor->stats.speed = stats.speed;
  actor->stats.normalSpeed = stats.normalSpeed;
  actor->stats.attackModifier = stats.attackModifier;
  i = 0;
  while (i < spellBook.spellList.size())
    {
      actor->spellBook.spellList.push_back(spellBook.spellList[i]);
      ++i;
    }
  actor->setCollide(collideActive);
  actor->setTextureId(texture);
  actor->setMeshId(model);
  actor->changePos(coord);
  actor->changeSize(size);
  actor->changeOrientation(orientation);
  return (actor);
}

void		Actor::setMove()
{
  ismoving = !ismoving;
}

void Actor::addSpell(int spellEnum) {
  spellBook.addSpell(spellEnum, this);
}


