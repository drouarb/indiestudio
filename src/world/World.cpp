//
// World.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:58:51 2016 Esteban Lewis
// Last update Fri May 20 18:30:49 2016 Alexis Trouve
//

#include <iostream>
#include "World.hh"
#include "Math.hh"

using namespace	gauntlet;
using namespace world;

World::World()
{
  Factory = new BodyFactory(this);
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

void	World::gameLoop()
{
  while (42 == 42)
    {
      applyMoveActor();
    }
}

void	World::addNewBody(double xpos, double ypos, const std::string& name)
{
  ABody	*body;

  body = Factory->giveBody(name);
  body->setPos(make_pair(xpos, ypos));
  bodys.push_back(body);
  collider.setNewBodyNoCheckEntity(body);
}

void	World::tester()
{
  /*ABody	*newBody;

  std::cerr << "giveBody null work" << std::endl;
  if (Factory.giveBody(static_cast<BodyEnum>(538928)) == NULL)
    std::cerr << "ok" << std::endl;
  std::cerr << "giverealBody" << std::endl;
  if ((newBody = Factory.giveBody(BARBARE)) == NULL)
    std::cerr << "error return" << std::endl;
  std::cerr << newBody->getId() << " ok" << std::endl;
  std::cerr << "new guy in collider without real coord" << std::endl;
  if (collider.setNewBody(newBody) == false)
    std::cerr << "ok return" << std::endl;
  std::cerr << "ok" << std::endl;
  std::cerr << "new guy 80 80" << std::endl;
  newBody = Factory.giveBody(BARBARE);
  newBody->changePos(80, 80);
  std::cerr << "x80:" << newBody->getPos().first << " y80:"
	    << newBody->getPos().second << " id:" << newBody->getId() << " ok" << std::endl;
  std::cerr << "in collider with no one at 80, 80" << std::endl;
  if (collider.setNewBody(newBody) == true)
    std::cerr << "ok return" << std::endl;
  std::cerr << "ok" << std::endl;
  std::cerr << "new guy 80 80" << std::endl;
  newBody = Factory.giveBody(BARBARE);
  newBody->changePos(80, 80);
  std::cerr << "x80:" << newBody->getPos().first << " y80:"
	    << newBody->getPos().second <<" id:" << newBody->getId() << " ok" << std::endl;
  std::cerr << "in collider with no one at 80, 80" << std::endl;
  if (collider.setNewBody(newBody) == false)
    std::cerr << "ok return" << std::endl;
    std::cerr << "ok" << std::endl;*/
}

Collider&	World::getCollider()
{
  return (collider);
}
