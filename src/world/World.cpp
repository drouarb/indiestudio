//
// World.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:58:51 2016 Esteban Lewis
// Last update Sun May 22 19:01:15 2016 Esteban Lewis
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "World.hh"
#include "Math.hh"
#include "IJson.hpp"

using namespace	gauntlet;
using namespace world;

World::World()
{
  IAs.push_back(new BasicIA(this));
  Factory = new BodyFactory(this, IAs);
  collider = NULL;
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
  std::ifstream is(file.c_str());

  if (!is)
    throw (std::runtime_error("Could not read file '" + file + "'"));

  std::string content("");
  std::string tmp;
  while (!is.eof())
    {
      is >> tmp;
      content += tmp;
    }

  JSON::JsonObj json;
  json.ParseFrom(content);

  collider = new Collider(stoi(dynamic_cast<JSON::JsonStr &>(json.GetObj("length")).Get()),
			  stoi(dynamic_cast<JSON::JsonStr &>(json.GetObj("width")).Get()));

  JSON::JsonObj & spawn = dynamic_cast<JSON::JsonObj &>(json.GetObj("spawn"));
  dynamic_cast<JSON::JsonStr &>(spawn.GetObj("x"));
  dynamic_cast<JSON::JsonStr &>(spawn.GetObj("y"));

  dynamic_cast<JSON::JsonStr &>(json.GetObj("map"));

  JSON::JsonArr & arr = dynamic_cast<JSON::JsonArr &>(json.GetObj("dynamic"));
  for (int i = 0; i < arr.Size(); ++i)
    {
      JSON::JsonObj & obj = dynamic_cast<JSON::JsonObj &>(arr[i]);
      addNewBody(stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()),
		 stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get()),
		 dynamic_cast<JSON::JsonStr &>(obj.GetObj("name")).Get(),
		 Math::getAngleFromDegrees
		 (stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("angle")).Get())));
    }

  JSON::JsonArr & arr_p = dynamic_cast<JSON::JsonArr &>(json.GetObj("physical"));
  for (int i = 0; i < arr_p.Size(); ++i)
    {
      JSON::JsonObj & obj = dynamic_cast<JSON::JsonObj &>(arr_p[i]);
      (void)obj;
    }
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
