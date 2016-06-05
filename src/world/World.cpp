#include <iostream>
#include <fstream>
#include <stdexcept>
#include <graph/Animations.hh>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "World.hh"
#include "IJson.hpp"
#include "Rand.hh"
#include "SpawnerAI.hh"
#include "DistAI.hh"

using namespace gauntlet;
using namespace world;

World::World(GameServer *ngameserver)
{
  std::cout << "world created" << std::endl;
  AIs.push_back(new BasicAI(this));
  AIs.push_back(new BasicAI(this));
  AIs.push_back(new SpawnerAI(this));
  Factory = new BodyFactory(this, AIs);
  collider = NULL;
  Math::init();
  musicHandler.setWorld(this);
  sizeX = 0;
  sizeY = 0;
  gameServer = ngameserver;
  looper = true;
  std::cout << "world created end" << std::endl;
}

World::~World()
{ }

void    World::loadGame(std::string const &file)
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

  mapAssetName = dynamic_cast<JSON::JsonStr &>(json.GetObj("asset_map")).Get();

  mapHeightName = dynamic_cast<JSON::JsonStr &>(json.GetObj("height_map")).Get();

  collider = new Collider(mapHeightName);
  sizeX = collider->getSizeMap().first;
  sizeY = collider->getSizeMap().second;

  try
    {
      JSON::JsonObj &endZone = dynamic_cast<JSON::JsonObj &>(json.GetObj("endZone"));
      endPos.first = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("posX")).Get()) * HEIGHT_MAP_SCALE;
      endPos.second = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("posY")).Get()) * HEIGHT_MAP_SCALE;
      endSize.first = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("sizeX")).Get()) * HEIGHT_MAP_SCALE;
      endSize.second = stod(dynamic_cast<JSON::JsonStr &>(endZone.GetObj("sizeY")).Get()) * HEIGHT_MAP_SCALE;

      JSON::JsonObj &spawn = dynamic_cast<JSON::JsonObj &>(json.GetObj("spawn"));
      spawnPoint.first = stod(dynamic_cast<JSON::JsonStr &>(spawn.GetObj("x")).Get()) * HEIGHT_MAP_SCALE;
      spawnPoint.second = stod(dynamic_cast<JSON::JsonStr &>(spawn.GetObj("y")).Get()) * HEIGHT_MAP_SCALE;

      if (spawnPoint.first < 0 || spawnPoint.first >= sizeX ||
	  spawnPoint.second < 0 || spawnPoint.second >= sizeY)
	throw (std::runtime_error("Spawn point coordinates are out of bounds"));
      JSON::JsonArr &arr = dynamic_cast<JSON::JsonArr &>(json.GetObj("dynamic"));

      for (unsigned int i = 0; i < arr.Size(); ++i)
	{
	  JSON::JsonObj &obj = dynamic_cast<JSON::JsonObj &>(arr[i]);
	  addNewBody(stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()) * HEIGHT_MAP_SCALE,
		     stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get()) * HEIGHT_MAP_SCALE,
		     dynamic_cast<JSON::JsonStr &>(obj.GetObj("name")).Get(),
		     Math::getAngleFromDegrees
		     (stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("angle")).Get())));
	}
      JSON::JsonArr &sounds = dynamic_cast<JSON::JsonArr &>(json.GetObj("sounds"));

      for (unsigned int i = 0; i < sounds.Size(); ++i)
	{
	  JSON::JsonObj &obj = dynamic_cast<JSON::JsonObj &>(sounds[i]);
	  putSound(stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("id")).Get()),
		   std::pair<double, double>
		   (stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()) * HEIGHT_MAP_SCALE,
		    stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get()) * HEIGHT_MAP_SCALE));
	}
      JSON::JsonArr &particles = dynamic_cast<JSON::JsonArr &>
	(json.GetObj("particles"));

      for (unsigned int i = 0; i < particles.Size(); ++i)
	{
	  JSON::JsonObj &obj = dynamic_cast<JSON::JsonObj &>(particles[i]);
	  putEffect(stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj("id")).Get()),
		    Math::getAngleFromDegrees
		    (stoi(dynamic_cast<JSON::JsonStr &>(obj.GetObj(
								   "angle")).Get())),
		    std::pair<double, double>
		    (stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("x")).Get()) * HEIGHT_MAP_SCALE,
		     stod(dynamic_cast<JSON::JsonStr &>(obj.GetObj("y")).Get()) * HEIGHT_MAP_SCALE));
	}
    }
  catch (std::runtime_error &e)
    {
      std::cout << "error loader" << std::endl;
      if (collider)
	delete collider;
      collider = NULL;
      throw e;
    }
}

JSON::JsonStr World::doubleToJsonStr(double d)
{
  std::stringstream ss;

  ss << d;
  return (JSON::JsonStr(ss.str()));
}

JSON::JsonStr World::intToJsonStr(int d)
{
  std::stringstream ss;

  ss << d;
  return (JSON::JsonStr(ss.str()));
}

JSON::JsonStr World::angleToJsonStr(int a)
{
  std::stringstream ss;

  a = (a * 360) / Math::A_FULL;
  ss << a;
  return (JSON::JsonStr(ss.str()));
}

bool    World::saveGame(std::string const &file)
{
  std::ofstream os(file);
  if (!os)
    return (false);

  JSON::JsonObj root;

  root.AddObj("name", JSON::JsonStr("Saved game"));
  root.AddObj("asset_map", JSON::JsonStr(this->mapAssetName));
  root.AddObj("height_map", JSON::JsonStr(this->mapHeightName));

  JSON::JsonObj endZone;
  endZone.AddObj("posX", doubleToJsonStr(endPos.first / HEIGHT_MAP_SCALE));
  endZone.AddObj("posY", doubleToJsonStr(endPos.second / HEIGHT_MAP_SCALE));
  endZone.AddObj("sizeX", doubleToJsonStr(endSize.first / HEIGHT_MAP_SCALE));
  endZone.AddObj("sizeY", doubleToJsonStr(endSize.second / HEIGHT_MAP_SCALE));
  root.AddObj("endZone", endZone);

  JSON::JsonObj spawn;
  spawn.AddObj("x", doubleToJsonStr(spawnPoint.first / HEIGHT_MAP_SCALE));
  spawn.AddObj("y", doubleToJsonStr(spawnPoint.second / HEIGHT_MAP_SCALE));
  root.AddObj("spawn", spawn);

  JSON::JsonArr dynamic;
  for (std::list<ABody *>::iterator it = bodys.begin(); it != bodys.end(); ++it)
    {
      if (dynamic_cast<Player *>(*it) == NULL)
	{
	  JSON::JsonObj obj;
	  obj.AddObj("name", JSON::JsonStr((*it)->getName()));
	  obj.AddObj("angle", angleToJsonStr((*it)->getOrientation()));
	  obj.AddObj("x", doubleToJsonStr((*it)->getPos().first / HEIGHT_MAP_SCALE));
	  obj.AddObj("y", doubleToJsonStr((*it)->getPos().second / HEIGHT_MAP_SCALE));
	  dynamic.AddObj(obj);
	}
    }
  root.AddObj("dynamic", dynamic);

  JSON::JsonArr sounds;
  for (std::vector<soundGlobal *>::iterator it = soundTab.begin(); it != soundTab.end(); ++it)
    {
      if ((*it)->loop)
	{
	  JSON::JsonObj obj;
	  obj.AddObj("id", intToJsonStr((*it)->soundId));
	  obj.AddObj("x", doubleToJsonStr((*it)->pos.first / HEIGHT_MAP_SCALE));
	  obj.AddObj("y", doubleToJsonStr((*it)->pos.second / HEIGHT_MAP_SCALE));
	  sounds.AddObj(obj);
	}
    }
  root.AddObj("sounds", sounds);

  JSON::JsonArr particles;
  for (std::vector<effectGlobal *>::iterator it = effectTab.begin(); it != effectTab.end(); ++it)
    {
      if ((*it)->decayTime <= 0)
	{
	  JSON::JsonObj obj;
	  obj.AddObj("id", intToJsonStr((*it)->effectId));
	  obj.AddObj("x", doubleToJsonStr((*it)->pos.first / HEIGHT_MAP_SCALE));
	  obj.AddObj("y", doubleToJsonStr((*it)->pos.second / HEIGHT_MAP_SCALE));
	  particles.AddObj(obj);
	}
    }
  root.AddObj("particles", particles);

  os << root.Serialize();
  os.close();
  return (true);
}

void    World::applyMoveActor()
{
  std::list<ABody *>::iterator it1;
  ABody *body;
  Actor *actor;

  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      body = (*it1);
      if ((actor = dynamic_cast<Actor *>(body)) != NULL)
	{
	  actor->move();
	  gameServer->sendMoveId(actor);
	}
      it1++;
    }
}

void        World::applyAI()
{
  std::list<ABody *>::iterator it1;
  unsigned int i;
  unsigned int j;
  std::vector<Player *> players;
  Player *nplay;

  it1 = bodys.begin();
  while (it1 != bodys.end())
    {
      if ((nplay = dynamic_cast<Player *>(*it1)) != NULL)
	{
	  players.push_back(nplay);
	}
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
}

void        World::checkHUD()
{
  std::vector<playerServerData> players;
  unsigned int i;
  ABody *body;
  Actor *actor;

  i = 0;
  players = gameServer->getPlayers();
  while (i < players.size())
    {
      body = getBodyById(players[i].idPlayer);
      if ((actor = dynamic_cast<Actor *>(body)) != NULL)
	{
	  gameServer->sendHUD(actor->getId(), static_cast<int>(
							       (static_cast<double>(actor->stats.HP) / static_cast<double>(actor->stats.normalHP)) * 100));
	}
      ++i;
    }
}

void        World::gameLoop()
{
  stopwatch.set();
  turn = 0;
  while (looper == true)
    {
      if (stopwatch.ellapsedMs() < ROUND_DURATION)
#ifdef _WIN32
	Sleep(ROUND_DURATION - stopwatch.ellapsedMs());
#else
	usleep(ROUND_DURATION * 1000 - stopwatch.ellapsedMs() * 1000);
#endif
      stopwatch.set();
      if (turn % AI_PRIORITY == 0)
	applyAI();
      applyMoveActor();
      if (turn % GATHERING_PRIORITY == 0)
	applyGatheringAndOpening();
      if (turn % WIN_PRIORITY == 0)
	checkWin();
      if (turn % RESPAWN_PRIORITY == 0)
	checkRespawn();
      if (turn % AUTOSHIFT_PRIORITY == 0)
	collider->autoShift();
      if (turn % HUD_PRIORITY == 0)
	checkHUD();
      ++turn;
    }
}

void    World::checkRespawn()
{
  unsigned int i;
  Player *player;

  i = 0;
  while (i < deathPlayers.size())
    {
      deathPlayers[i].coolDownRespawn -= RESPAWN_PRIORITY;
      if (deathPlayers[i].coolDownRespawn <= 0)
	{
	  player = deathPlayers[i].player;
	  player->stats.HP = player->stats.normalHP;
	  player->changePos(spawnPoint);
	  gameServer->sendMoveId(deathPlayers[i].player);
	  collider->setNewBodyNoCheckEntity(player);
	  deathPlayers.erase(deathPlayers.begin() + i);
	  break;
	}
      ++i;
    }
}

void        World::notifyDeath(ABody *body)
{
  std::cout << "world notify Death" << std::endl;
  unsigned int			i;
  Player			*player;
  Spawner			*spawner;
  std::list<ABody*>::iterator	it;
  ABody				*sbody;

  std::cout << "on notify une mort OMG id : " << body->getId() << std::endl;
  collider->suprBody(body->getId());
  i = 0;
  while (i < AIs.size())
    {
      AIs[i]->suprActor(body->getId());
      ++i;
    }
  if ((player = dynamic_cast<Player *>(body)) != NULL)
    deathPlayers.push_back({DEATH_COOLDOWN_NB_TURN, player});
  else
    {
      it = bodys.begin();
      while (it != bodys.end())
	{
	  sbody = (*it);
	  if ((spawner = dynamic_cast<Spawner*>(body)) != NULL)
	    spawner->deleteId(body->getId());
	  ++it;
	}
      it = bodys.begin();
      while (it != bodys.end())
	{
	  if (sbody->getId() == body->getId())
	    {
	      bodys.erase(it);
	      break;
	    }
	  ++it;
	}
    }
  std::cout << "world notify Death end" << std::endl;
}

void    World::checkWin()
{
  std::list<ABody *>::iterator it;
  ABody *body;
  Player *player;
  bool pass;

  it = bodys.begin();
  pass = false;
  while (it != bodys.end())
    {
      body = (*it);
      if ((player = dynamic_cast<Player *>(body)) != NULL)
	{
	  pass = true;
	  if (player->getPos().first >= endPos.first
	      && player->getPos().first <= endPos.first + endSize.first
	      && player->getPos().second >= endPos.second
	      && player->getPos().second <= endPos.second + endSize.second)
	    {
	      std::cout << "win" << std::endl;
	      gameServer->decoAll("Victory!");
	      looper = false;
	    }
	}
      it++;
    }
  if (pass == false)
    return;
}

void    World::applyGatheringAndOpening()
{
  std::list<ABody *>::iterator it;
  std::list<ABody *>::iterator it2;
  Player *player;
  GameObject *gameobject;
  ABody *body;
  std::list<ABody *> list;

  it = bodys.begin();
  while (it != bodys.end())
    {
      body = (*it);
      if ((player = dynamic_cast<Player *>(body)) != NULL)
	{
	  list = collider->giveBodyInAreaCircle(player->getPos().first,
						player->getPos().second, 0,
						(player->getSize().first +
						 player->getSize().second * 2.0), 0);
	  if (list.size() > 0)
	    {
	      it2 = list.begin();
	      while (it2 != list.end())
		{
		  body = (*it2);
		  if ((gameobject = dynamic_cast<GameObject *>(body)) != NULL)
		    {
		      gameobject->open(&player->inventory);
		      if (gameobject->gather(player) == true)
			deleteId(gameobject->getId(), true);
		    }
		  it2++;
		}
	    }
	}
      it++;
    }
}

int    World::addNewBody(double xpos, double ypos, const std::string &name,
                         short orientation)
{
  std::cout << "world addnewbody pos:" << xpos << ":" << ypos << " name:" << name << std::endl;

  ABody *body;
  std::pair<unsigned int, unsigned int> sizeMap;

  if ((body = Factory->giveBody(name)) == NULL)
    throw (std::runtime_error(name + " does not exist"));
  if ((xpos - (body->getSize().first / 2.0)) < 0 ||
      (xpos + (body->getSize().first / 2.0)) >= sizeX
      || (ypos - (body->getSize().second / 2.0)) < 0 ||
      (ypos + (body->getSize().second / 2.0)) >= sizeY)
    {
      std::cout << "error" << std::endl;
      throw (std::runtime_error(name + " is out of bounds"));
      exit(0);
    }
  if (body == NULL)
    {
      throw (std::runtime_error("'" + name + "': wrong name"));
      exit(0);
    }
  body->changePos(std::make_pair(xpos, ypos));
  body->changeOrientation(orientation);
  gameServer->sendAddEntity(body);
  bodys.push_back(body);
  collider->setNewBodyNoCheckEntity(body);
  std::cout << "world addnewbody end" << std::endl;
  return (body->getId());
}

void        World::deleteId(int id, bool deleted)
{
  std::cout << "world deleteId" << std::endl;
  unsigned int i;
  std::list<ABody *>::iterator it1;
  ABody *body;

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
  if (deleted == true)
    delete (body);
  std::cout << "world deleteId end" << std::endl;
}

Collider &World::getCollider()
{
  return (*collider);
}

const std::pair<double, double> &World::getSpawnPoint()
{
  return (spawnPoint);
}

std::list<ABody *>        World::getBodysByCopy() const
{
  return (bodys);
}

int                World::getUniqueEffectId()
{
  static int i = -1;

  return (++i);
}

void                World::putEffect(unsigned int effectId, short orient,
                                     const std::pair<double, double> &pos)
{
  int id;
  effectGlobal *eff;

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

int                World::triggerEffect(gauntlet::EffectName effect,
                                        short orient,
                                        const std::pair<double, double> &pos,
                                        int decayTime)
{
  int id;
  unsigned int effectId;
  effectGlobal *eff;

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

int                World::triggerEffect(gauntlet::EffectName effect,
                                        const std::pair<double, double> &pos,
                                        int decayTime)
{
  int id;
  unsigned int effectId;
  effectGlobal *eff;

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

void                World::stopEffect(int id)
{
  unsigned int i;
  effectGlobal *effect;

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

int                World::getUniqueSoundId()
{
  static int id = -1;

  return (++id);
}

void                World::putSound(unsigned int soundId,
                                    const std::pair<double, double> &pos)
{
  int id;
  soundGlobal *sound;

  id = getUniqueEffectId();
  gameServer->sendSound(soundId, id, true, pos);
  sound = new soundGlobal;
  sound->Id = id;
  sound->pos = pos;
  sound->soundId = soundId;
  sound->loop = true;
  soundTab.push_back(sound);
}

int                World::playSound(unsigned int soundId, bool loop,
                                    const std::pair<double, double> &pos)
{
  int id;
  soundGlobal *sound;

  id = getUniqueEffectId();
  gameServer->sendSound(soundId, id, loop, pos);
  if ((sound = new soundGlobal) == NULL)
    exit(0);
  sound->Id = id;
  sound->pos = pos;
  sound->soundId = soundId;
  sound->loop = loop;
  soundTab.push_back(sound);
  return (id);
}

void                World::stopSound(int idToStop)
{
  unsigned int i;
  soundGlobal *sound;

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

std::vector<effectGlobal *>    World::getEffectByCopy() const
{
  return (effectTab);
}

std::vector<soundGlobal *>    World::getSoundByCopy() const
{
  return (soundTab);
}

void                World::applyCommand(short angle, int id, core::Command command)
{
  Player *player;
  ABody *body;

  body = getBodyById(id);
  if ((player = dynamic_cast<Player *>(body)) == NULL)
    return;
  if (player->stats.HP <= 0.0)
    return;
  body->changeOrientation(angle);
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
      applyCommand(angle, id, core::UP_STOP);
      player->castSpell(command - core::ATTACK1);
    }
}

ABody *World::getBodyById(int id)
{
  std::list<ABody *>::iterator it;

  it = bodys.begin();
  while (it != bodys.end())
    {
      if (id == ((*it)->getId()))
	return ((*it));
      it++;
    }
  return (NULL);
}

void                World::animeEntity(int id, unsigned int animeId, bool loop)
{
  std::cerr << "id:" << id << " anime:" << animeId << std::endl;
  gameServer->animeEntity(id, animeId, loop);
}

unsigned long            World::getTurn() const
{
  return (turn);
}

std::string        World::getMapNames() const
{
  return (mapAssetName + ";" + mapHeightName);
}

std::pair<double, double>    World::getSize() const
{
  return (std::make_pair(sizeX, sizeY));
}

void                World::setLooper(bool nloop)
{
  looper = nloop;
}

MusicHandler *World::getMusicHandler() {
  return &musicHandler;
}
