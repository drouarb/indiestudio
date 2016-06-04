//
// Spawner.cpp for Spawner in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Fri Jun  3 21:56:39 2016 Alexis Trouve
// Last update Sat Jun  4 18:00:59 2016 Alexis Trouve
//

#include "Spawner.hh"
#include "Math.hh"
#include "World.hh"

using namespace gauntlet;

Spawner::Spawner(int nid, gauntlet::world::World *newWorld) : Creature(nid, newWorld)
{

}

Spawner::~Spawner()
{
}

int		Spawner::getNbLinkedCreature()
{
  std::list<Creature*>::iterator	it;
  int				result;

  it = myCrea.begin();
  result = 0;
  while (it != myCrea.end())
    {
      if ((*it)->stats.HP > 0.0)
	result++;
      ++it;
    }
  return (result);
}

void		Spawner::spawnAllie(std::pair<double, double>& endPos)
{
  if (getNbLinkedCreature() >= maxSpawn)
    return ;
  if (world->getCollider().canMove(coord, endPos, size) == false)
    return ;
  world->addNewBody(endPos.first, endPos.second, minionName, orientation);
}

int		Spawner::getMaxSpawn() const
{
  return (maxSpawn);
}

void		Spawner::setMaxSpawn(int nbr)
{
  maxSpawn = nbr;
}

const std::list<Creature*>&	Spawner::getCreature() const
{
  return (myCrea);
}

const std::string&		Spawner::getMinionName() const
{
  return (minionName);
}

void				Spawner::setMinionName(const std::string& nname)
{
  minionName = nname;
}

int				Spawner::getSpawnCoolDown() const
{
  return (spawnCoolDown);
}

int				Spawner::getSpawnCoolDownBase() const
{
  return (spawnCoolDownBase);
}

void				Spawner::setSpawnCoolDown(int nbr)
{
  spawnCoolDown = nbr;
}

void				Spawner::setSpawnCoolDownBase(int nbr)
{
  spawnCoolDownBase = nbr;
}

ABody           *Spawner::clone(int id) const
{
  Spawner         *spawn;
  unsigned int  i;

  spawn = new Spawner(id, world);
  spawn->setName(name);
  spawn->stats.HP = stats.HP;
  spawn->stats.normalHP = stats.normalHP;
  spawn->stats.speed = stats.speed;
  spawn->stats.normalSpeed = stats.normalSpeed;
  spawn->stats.attackModifier = stats.attackModifier;
  i = 0;
  while (i < spellBook.spellList.size())
    {
      spawn->spellBook.spellList.push_back(spellBook.spellList[i]);
      ++i;
    }
  spawn->setCollide(collideActive);
  spawn->setTextureId(texture);
  spawn->setMeshId(model);
  spawn->setIdle(idle);
  spawn->setRunning(running);
  spawn->changePos(coord);
  spawn->death = this->death;
  spawn->changeSize(size);
  spawn->changeOrientation(orientation);
  spawn->setIdAI(idAI);
  spawn->setSpawnCoolDown(spawnCoolDown);
  spawn->setSpawnCoolDownBase(spawnCoolDownBase);
  spawn->setMinionName(minionName);
  spawn->setMaxSpawn(maxSpawn);
  return (spawn);
}
