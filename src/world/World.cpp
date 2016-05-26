//
// World.cpp for indie in /home/lewis_e/rendu/cpp/cpp_indie_studio
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon May  9 14:58:51 2016 Esteban Lewis
// Last update Thu May 26 11:17:46 2016 Alexis Trouve
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unistd.h>
#include "World.hh"
#include "Math.hh"
#include "IJson.hpp"

using namespace	gauntlet;
using namespace world;

World::World(GameServer *ngameserver)
{
  std::cout << "world created" << std::endl;
  AIs.push_back(new BasicAI(this));
  Factory = new BodyFactory(this, AIs);
  collider = NULL;
  Math::init();
  sizeX = 0;
  sizeY = 0;
  gameServer = ngameserver;
  std::cout << "world created end" << std::endl;
}

World::~World()
{ }

void	World::update()
{
  std::cout << "WORLD update" << std::endl;
}

void	World::loadGame(std::string const & file)
{
  std::cout << "world loadGame" << std::endl;
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

  try
    {
      sizeX = stoi(dynamic_cast<JSON::JsonStr &>(json.GetObj("length")).Get());
      sizeY = stoi(dynamic_cast<JSON::JsonStr &>(json.GetObj("width")).Get());
      collider = new Collider(sizeX, sizeY);
      
      JSON::JsonObj & spawn = dynamic_cast<JSON::JsonObj &>(json.GetObj("spawn"));
      spawnPoint.first = stod(dynamic_cast<JSON::JsonStr &>(spawn.GetObj("x")).Get());
      spawnPoint.second = stod(dynamic_cast<JSON::JsonStr &>(spawn.GetObj("y")).Get());
      if (spawnPoint.first < 0 || spawnPoint.first >= sizeX ||
	  spawnPoint.second < 0 || spawnPoint.second >= sizeY)
	throw (std::runtime_error("Spawn point coordinates are out of bounds"));

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
  catch (std::runtime_error & e)
    {
      if (collider)
	delete collider;
      collider = NULL;
      throw e;
    }
  std::cout << "world loadGame end" << std::endl;
}

void	World::applyMoveActor()
{
  std::cout << "world applyMoveActor" << std::endl;
  std::list<ABody*>::iterator	it1;
  ABody				*body;
  Actor				*actor;

  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      body = (*it1);
      if ((actor = dynamic_cast<Actor*>(body)) != NULL)
	{
	  actor->move();
	  gameServer->sendMoveId(actor);
	}
      it1++;
    }
  std::cout << "world applyMoveActor end" << std::endl;
}

void		World::applyAI()
{
  std::cout << "world applyAI" << std::endl;
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
      while (i < AIs.size())
	{
	  AIs[i]->launchAI(players[j]->getPos());
	  ++i;
	}
      ++j;
    }
  std::cout << "world applyAI end" << std::endl;
}

void		World::gameLoop()
{
  std::cout << "world gameLoop" << std::endl;
  unsigned int i;
  Actor *actor;
  ABody	*body;
  std::list<ABody*>::iterator it1;
  it1 = bodys.begin();
  sleep(1);
  while (it1 != bodys.end())
    {
      body = (*it1);
      if ((actor = dynamic_cast<Actor*>(body)) != NULL)
	if (actor->getMove() == false)
	  actor->setMove();
      it1++;
    }
  while (42 == 42)
    {
      usleep(100000);
      //TODO: frequency
      applyAI();
      applyMoveActor();
    }
  std::cout << "world gameLoop end" << std::endl;
}

int	World::addNewBody(double xpos, double ypos, const std::string& name, short orientation)
{
  std::cout << "world addnewbody" << std::endl;
  ABody	*body;

  if (xpos < 0 || xpos >= sizeX || ypos < 0 || ypos >= sizeY)
    throw (std::runtime_error(name + " is out of bounds"));
  body = Factory->giveBody(name);
  if (body == NULL)
    throw (std::runtime_error("'" + name + "': wrong name"));
  body->changePos(std::make_pair(xpos, ypos));
  body->changeOrientation(orientation);
  gameServer->sendAddEntity(body);
  bodys.push_back(body);
  collider->setNewBodyNoCheckEntity(body);
  std::cout << "world addnewbody end" << std::endl;
  return (body->getId());
}

void		World::notifyDeath(ABody *body)
{
  std::cout << "world notify Death" << std::endl;
  unsigned int	i;

  collider->suprBody(body->getId());
  i = 0;
  while (i < AIs.size())
    {
      AIs[i]->suprActor(body->getId());
      ++i;
    }
  std::cout << "world notify Death end" << std::endl;
}

void		World::deleteId(int id)
{
  std::cout << "world deleteId" << std::endl;
  unsigned int	i;
  std::list<ABody*>::iterator it1;

  collider->suprBody(id);
  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      if (id == (*it1)->getId())
	bodys.erase(it1);
      it1++;
    }
  i = 0;
  while (i < AIs.size())
    {
      AIs[i]->suprActor(id);
      ++i;
    }
  std::cout << "world deleteId end" << std::endl;
}

Collider&	World::getCollider()
{
  return (*collider);
}

const std::pair<double, double>&	World::getSpawnPoint()
{
  return (spawnPoint);
}

std::list<ABody*>		World::getBodysByCopy() const
{
  return (bodys);
}

int				World::getUniqueEffectId()
{
  static int			i = -1;

  return (++i);
}

int				World::triggerEffect(gauntlet::EffectName effect)
{
  int				id;

  id = getUniqueEffectId();
  effectTab.push_back(id);
  return (id);
}

void				World::stopEffect(int id)
{
  int				i;

  i = 0;
  while (i < effectTab.size())
    {
      if (effectTab[i] == id)
	{
	  effectTab.erase(effectTab.begin() + i);
	  break;
	}
      ++i;
    }
}
