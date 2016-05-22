#include <iostream>
#include "World.hh"
#include "Math.hh"
#include "IJson.hpp"

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

void	World::loadGame(std::string const & file)
{
  
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

void	World::gameLoop()
{
  while (42 == 42)
    {
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
  collider.setNewBodyNoCheckEntity(body);
}

void		World::notifyDeath(ABody *body)
{
  unsigned int	i;

  collider.suprBody(body->getId());
  i = 0;
  while (i < IAs.size())
    {
      IAs[i]->suprActor(body->getId());
      ++i;
    }
}

Collider&	World::getCollider()
{
  return (collider);
}
