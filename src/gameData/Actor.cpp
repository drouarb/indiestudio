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
  idAI = -1;
}

Actor::~Actor()
{
}

void        Actor::setStance()
{
  /*  if (ismoving)
      this->getWorld()->animeEntity(this->id, running);
    else
      this->getWorld()->animeEntity(this->id, idle);*/
}

void		Actor::move()
{
  setStance();
  if (ismoving)
    {
      world->getCollider().applyVectorToId(id, orientation, stats.speed);
    }
}

bool		Actor::getMove() const
{
  return (ismoving);
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
  actor->setIdle(idle);
  actor->setRunning(running);
  actor->changePos(coord);
  actor->changeSize(size);
  actor->changeOrientation(orientation);
  actor->setIdAI(idAI);
  return (actor);
}

void        Actor::castSpell(int spellEnum)
{
  if (recharged() && spellEnum < (int)spellBook.spellList.size())
  {
    spellBook.spellList[spellEnum]->prepare(this);
    spellBook.spellList[spellEnum]->cast(this);
  }
}

void		Actor::setMove()
{
  if (recharged())
    ismoving = !ismoving;
}

void Actor::addSpell(int spellEnum) {
  spellBook.addSpell(spellEnum, this);
}

void		Actor::setIdAI(int ia)
{
  idAI = ia;
}

int		Actor::getIdAI() const
{
  return (idAI);
}
