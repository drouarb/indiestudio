//
// World.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sat May 28 16:36:35 2016 Alexis Trouve
// Last update Sun May 29 14:01:42 2016 Alexis Trouve
//

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <unistd.h>
#include "World.hh"
#include "IJson.hpp"
#include "Rand.hh"

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
      mapAssetName = dynamic_cast<JSON::JsonStr &>(json.GetObj("asset_map")).Get();

      mapHeightName = dynamic_cast<JSON::JsonStr &>(json.GetObj("height_map")).Get();

      collider = new Collider(mapHeightName);

      std::cout << "x:" << (sizeX = collider->getSizeMap().first) << std::endl;
      std::cout << "y:" << (sizeY = collider->getSizeMap().second) << std::endl;

      JSON::JsonObj & endZone = dynamic_cast<JSON::JsonObj &>(json.GetObj("endZone"));
      endPos.first = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("posX")).Get());
      endPos.second = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("posY")).Get());
      endSize.first = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("sizeX")).Get());
      endSize.second = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("sizeX")).Get());
      
      JSON::JsonObj & spawn = dynamic_cast<JSON::JsonObj &>(json.GetObj("spawn"));
      spawnPoint.first = stod(dynamic_cast<JSON::JsonStr &>(spawn.GetObj("x")).Get());
      spawnPoint.second = stod(dynamic_cast<JSON::JsonStr &>(spawn.GetObj("y")).Get());
      if (spawnPoint.first < 0 || spawnPoint.first >= sizeX ||
	  spawnPoint.second < 0 || spawnPoint.second >= sizeY)
	throw (std::runtime_error("Spawn point coordinates are out of bounds"));

      JSON::JsonArr & arr = dynamic_cast<JSON::JsonArr &>(json.GetObj("dynamic"));
      for (unsigned int i = 0; i < arr.Size(); ++i)
	{
	  JSON::JsonObj & obj = dynamic_cast<JSON::JsonObj &>(arr[i]);
	  addNewBody(stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()),
		     stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get()),
		     dynamic_cast<JSON::JsonStr &>(obj.GetObj("name")).Get(),
		     Math::getAngleFromDegrees
		     (stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("angle")).Get())));
	}

      JSON::JsonArr & sounds = dynamic_cast<JSON::JsonArr &>(json.GetObj("sounds"));
      for (unsigned int i = 0; i < sounds.Size(); ++i)
	{
	  JSON::JsonObj & obj = dynamic_cast<JSON::JsonObj &>(sounds[i]);
	  putSound(stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("id")).Get()),
		   std::pair<double, double>
		   (stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()),
		    stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get())));
	}

      JSON::JsonArr & particles = dynamic_cast<JSON::JsonArr &>
	(json.GetObj("particles"));
      for (unsigned int i = 0; i < particles.Size(); ++i)
	{
	  JSON::JsonObj & obj = dynamic_cast<JSON::JsonObj &>(particles[i]);
	  putEffect(stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("id")).Get()),
		    Math::getAngleFromDegrees
		    (stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("angle")).Get())),
		    std::pair<double, double>
		    (stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()),
		     stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get())));
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
}

void		World::applyAI()
{
  std::list<ABody*>::iterator	it1;
  unsigned int	i;
  unsigned int	j;
  std::vector<Player*>	players;
  Player		*nplay;

  it1 = bodys.begin();
  //std::cout << "1" << std::endl;
  while (it1 != bodys.end())
    {
      //std::cout << "2" << std::endl;
      if ((nplay = dynamic_cast<Player*>(*it1)) != NULL)
	{
	  //std::cout << "3" << std::endl;
	  players.push_back(nplay);
	}
      //std::cout << "4" << std::endl;
      it1++;
    }
  //std::cout << "5" << std::endl;
  j = 0;
  //std::cout << "6" << std::endl;
  while (j < players.size())
    {
      //std::cout << "7" << std::endl;
      i = 0;
      //std::cout << "8" << std::endl;
      while (i < AIs.size())
	{
	  //std::cout << "9" << std::endl;
	  AIs[i]->launchAI(players[j]->getPos());
	  ++i;
	}
      //std::cout << "10" << std::endl;
      ++j;
    }
  //std::cout << "11" << std::endl;
}

void		World::gameLoop()
{
  std::cout << "world gameLoop" << std::endl;
  stopwatch.set();
  turn = 0;
  while (42)
    {
      if (stopwatch.ellapsedMs() < ROUND_DURATION)
	usleep(ROUND_DURATION * 1000 - stopwatch.ellapsedMs());
      stopwatch.set();
      if (turn % AI_PRIORITY == 0)
	applyAI();
      applyMoveActor();
      //if (turn % GATHERING_PRIORITY == 0)
      //applyGatheringAndOpening();
      if (turn % WIN_PRIORITY == 0)
	checkWin();
      if (turn % RESPAWN_PRIORITY == 0)
	checkRespawn();
      ++turn;
    }
  std::cout << "world gameLoop end" << std::endl;
}

void	World::checkRespawn()
{
  unsigned int		i;
  Player		*player;

  i = 0;
  while (i < deathPlayers.size())
    {
      deathPlayers[i].coolDownRespawn -= RESPAWN_PRIORITY;
      if (deathPlayers[i].coolDownRespawn)
	{
	  player = deathPlayers[i].player;
	  player->stats.HP = player->stats.normalHP;
	}
      ++i;
    }
}

void	World::checkWin()
{
  std::list<ABody*>::iterator	it;
  ABody				*body;
  Player			*player;
  bool				pass;

  it = bodys.begin();
  pass = false;
  while (it != bodys.end())
    {
      body = (*it);
      if ((player = dynamic_cast<Player*>(body)) != NULL)
	{
	  pass = true;
	  if (player->getPos().first < endPos.first
	      || player->getPos().first + player->getSize().first > endPos.first + endSize.first
	      || player->getPos().second < endPos.second
	      || player->getPos().second + player->getSize().second > endPos.second + endSize.second)
	    return ;
	}
      it++;
    }
  if (pass == false)
    return ;
  gameServer->decoAll("Good game, you win.");
  exit(0);
}

void	World::applyGatheringAndOpening()
{
  std::cout << "checkGather" << std::endl;
  std::list<ABody*>::iterator	it;
  std::list<ABody*>::iterator	it2;
  Player			*player;
  GameObject			*gameobject;
  ABody				*body;
  std::list<ABody*>		list;

  it = bodys.begin();
  std::cout << "1" << std::endl;
  while (it != bodys.end())
    {
  std::cout << "2" << std::endl;
      body = (*it);
  std::cout << "3" << std::endl;
      if ((player = dynamic_cast<Player*>(body)) != NULL)
	{
  std::cout << "4" << std::endl;
	  list = collider->giveBodyInAreaCircle(player->getPos().first, player->getPos().second, 0,
						(player->getSize().first + player->getSize().second) / 2.0, 0);
  std::cout << "5" << std::endl;
	  if (list.size() > 0)
	    {
  std::cout << "6" << std::endl;
	      it2 = list.begin();
  std::cout << "7" << std::endl;
	      while (it2 != list.end())
		{
  std::cout << "8" << std::endl;
		  body = (*it2);
  std::cout << "9" << std::endl;
		  if ((gameobject = dynamic_cast<GameObject*>(body)) != NULL)
		    {
  std::cout << "10" << std::endl;
		      gameobject->open(&player->inventory);
  std::cout << "11" << std::endl;
		      gameobject->gather(player);
  std::cout << "12" << std::endl;
		    }
  std::cout << "13" << std::endl;
		  it2++;
  std::cout << "14" << std::endl;
		}
  std::cout << "15" << std::endl;
	    }
  std::cout << "16" << std::endl;
	}
  std::cout << "17" << std::endl;
      it++;
    }
  std::cout << "checkGather end" << std::endl;
}

int	World::addNewBody(double xpos, double ypos, const std::string& name, short orientation)
{
  std::cout << "world addnewbody" << std::endl;
  ABody	*body;
  std::pair<unsigned int, unsigned int>	sizeMap;

  if ((body = Factory->giveBody(name)) == NULL)
    throw (std::runtime_error(name + " does not exist"));
  if ((xpos - (body->getSize().first / 2.0)) < 0 || (xpos + (body->getSize().first / 2.0)) >= sizeX
      || (ypos - (body->getSize().second / 2.0)) < 0 || (ypos + (body->getSize().second / 2.0)) >= sizeY)
    {
      std::cout << "error" << std::endl;
      throw (std::runtime_error(name + " is out of bounds"));
    }
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
  Player	*player;

  std::cout << "on notify une mort OMG id : " << body->getId() << std::endl;
  collider->suprBody(body->getId());
  i = 0;
  while (i < AIs.size())
    {
      AIs[i]->suprActor(body->getId());
      ++i;
    }
  if ((player = dynamic_cast<Player*>(body)) != NULL)
    deathPlayers.push_back({450, player});
  std::cout << "world notify Death end" << std::endl;
}

void		World::deleteId(int id)
{
  std::cout << "world deleteId" << std::endl;
  unsigned int	i;
  std::list<ABody*>::iterator it1;
  ABody				*body;

  collider->suprBody(id);
  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      if (id == (*it1)->getId())
	{
	  body = (*it1);
	  bodys.erase(it1);
	  break;
	}
      it1++;
    }
  i = 0;
  while (i < AIs.size())
    {
      AIs[i]->suprActor(id);
      ++i;
    }
  gameServer->sendDeleteEntity(body);
  delete (body);
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

void				World::putEffect(unsigned int effectId, short orient,
						 const std::pair<double, double>& pos)
{
  int				id;
  effectGlobal			*eff;

  id = getUniqueEffectId();
  gameServer->sendEffect(effectId, id, orient, pos, -1);
  eff = new effectGlobal;
  eff->Id = id;
  eff->pos = pos;
  eff->effectId = effectId;
  eff->orientation = orient;
  eff->decayTime = -1;
  effectTab.push_back(eff);
}

int				World::triggerEffect(gauntlet::EffectName effect, short orient,
						     const std::pair<double, double>& pos, int decayTime)
{
  int				id;
  unsigned int			effectId;
  effectGlobal			*eff;

  id = getUniqueEffectId();
  effectId = static_cast<unsigned int>(effect);
  gameServer->sendEffect(effectId, id, orient, pos, decayTime);
  eff = new effectGlobal;
  eff->Id = id;
  eff->pos = pos;
  eff->effectId = effectId;
  eff->orientation = orient;
  eff->decayTime = decayTime;
  effectTab.push_back(eff);
  return (id);
}

int				World::triggerEffect(gauntlet::EffectName effect,
						     const std::pair<double, double>& pos, int decayTime)
{
  int				id;
  unsigned int			effectId;
  effectGlobal			*eff;

  id = getUniqueEffectId();
  effectId = static_cast<unsigned int>(effect);
  gameServer->sendEffect(effectId, id, 0, pos, decayTime);
  eff = new effectGlobal;
  eff->Id = id;
  eff->pos = pos;
  eff->effectId = effectId;
  eff->orientation = Rand::generate() % 628;
  eff->decayTime = decayTime;
  effectTab.push_back(eff);
  return (id);
}

void				World::stopEffect(int id)
{
  unsigned int			i;
  effectGlobal			*effect;

  i = 0;
  while (i < effectTab.size())
    {
      if (effectTab[i]->Id == id)
	{
	  gameServer->sendStopEffect(id);
	  effect = effectTab[i];
	  effectTab.erase(effectTab.begin() + i);
	  delete (effect);
	  effect = NULL;
	  break;
	}
      ++i;
    }
}

int				World::getUniqueSoundId()
{
  static int			id = -1;

  return (++id);
}

void				World::putSound(unsigned int soundId, const std::pair<double, double>& pos)
{
  int				id;
  soundGlobal			*sound;

  id = getUniqueEffectId();
  gameServer->sendSound(soundId, id, true, pos);
  sound = new soundGlobal;
  sound->Id = id;
  sound->pos = pos;
  sound->soundId = soundId;
  sound->loop = true;
  soundTab.push_back(sound);
}

int				World::playSound(unsigned int soundId, bool loop,
						 const std::pair<double, double>& pos)
{
  int				id;
  soundGlobal			*sound;

  id = getUniqueEffectId();
  gameServer->sendSound(soundId, id, loop, pos);
  sound = new soundGlobal;
  sound->Id = id;
  sound->pos = pos;
  sound->soundId = soundId;
  sound->loop = loop;
  soundTab.push_back(sound);
  return (id);
}

void				World::stopSound(int idToStop)
{
  unsigned int			i;
  soundGlobal			*sound;

  i = 0;
  while (i < soundTab.size())
    {
      if (soundTab[i]->Id == idToStop)
	{
	  gameServer->sendStopSound(idToStop);
	  sound = soundTab[i];
	  soundTab.erase(soundTab.begin() + i);
	  delete (sound);
	  sound = NULL;
	  break;
	}
      ++i;
    }
}

std::vector<effectGlobal*>	World::getEffectByCopy() const
{
  return (effectTab);
}

std::vector<soundGlobal*>	World::getSoundByCopy() const
{
  return (soundTab);
}

void				World::applyCommand(int id, core::Command command)
{
  Player			*player;
  ABody				*body;

  body = getBodyById(id);
  if ((player = dynamic_cast<Player*>(body)) == NULL)
    return ;
  if (command == core::UP)
    {
      if (!player->getMove())
	player->setMove();
    }
  else if (command == core::UP_STOP)
    {
      if (player->getMove())
	player->setMove();
    }
  else if (command >= core::ATTACK1 && command <= core::ATTACK4)
    {
      applyCommand(id, core::UP_STOP);
      player->castSpell(command - core::ATTACK1);
    }
}

ABody				*World::getBodyById(int id)
{
  std::list<ABody*>::iterator	it;

  it = bodys.begin();
  while (it != bodys.end())
    {
      if (id == ((*it)->getId()))
	return ((*it));
      it++;
    }
  return (NULL);
}

void				World::animeEntity(int id, unsigned int animeId)
{
  gameServer->animeEntity(id, animeId);
}

unsigned long			World::getTurn() const
{
  return (turn);
}

std::string		World::getMapNames() const
{
  return (mapAssetName + ";" + mapHeightName);
}

std::pair<double, double>	World::getSize() const
{
  return (std::make_pair(sizeX, sizeY));
}
