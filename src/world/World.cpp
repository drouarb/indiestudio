//
// World.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:58:51 2016 Esteban Lewis
// Last update Sun May 22 18:53:11 2016 Alexis Trouve
//

#include <iostream>
#include "World.hh"
#include "Math.hh"

using namespace	gauntlet;
using namespace world;

World::World()
{
  IAs.push_back(new BasicIA(this));
  Factory = new BodyFactory(this, IAs);
  Math::init();
  sizeX = 0;
  sizeY = 0;
}

World::~World()
{ }

void	World::update()
{
  std::cout << "WORLD update" << std::endl;
}

void	World::loadGame(std::string file)
{
  std::cout << "WORLD load " << file << std::endl;
}

void	World::initNetwork()
{
  
}

void	World::applyMoveActor()
{
  std::list<ABody*>::iterator	it1;
  ABody				*body;
  Actor				*actor;

  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      if ((actor = dynamic_cast<Actor*>((*it1))) != NULL)
	actor->move();
      it1++;
    }
}

void		World::applyIA()
{
  std::list<ABody*>::iterator	it1;
  unsigned int	i;
  unsigned int	j;
  std::vector<Player*>	players;
  Player		*nplay;

  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      if ((nplay = dynamic_cast<Player*>(*it1)) != NULL)
	players.push_back(nplay);
      it1++;
    }
  j = 0;
  while (j < players.size())
    {
      i = 0;
      while (i < IAs.size())
	{
	  IAs[i]->launchIA(players[j]->getPos());
	  ++i;
	}
      ++j;
    }
}

void		World::gameLoop()
{
  while (42 == 42)
    {
      applyIA();
      applyMoveActor();
    }
}

void	World::addNewBody(double xpos, double ypos, const std::string& name, short orientation)
{
  ABody	*body;

  body = Factory->giveBody(name);
  body->changePos(std::make_pair(xpos, ypos));
  body->changeOrientation(orientation);
  bodys.push_back(body);
  collider->setNewBodyNoCheckEntity(body);
}

void		World::notifyDeath(ABody *body)
{
  unsigned int	i;

  collider->suprBody(body->getId());
  i = 0;
  while (i < IAs.size())
    {
      IAs[i]->suprActor(body->getId());
      ++i;
    }
}

Collider&	World::getCollider()
{
  return (*collider);
}
