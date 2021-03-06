#include <iostream>
#include "PlayerChars.hh"
#include "ServSelectPlayerListener.hh"
#include "ServConnectListener.hh"
#include "ServDisconnectListener.hh"
#include "ServControlListener.hh"
#include "ServMapListener.hh"
#include "GameServer.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

GameServer::GameServer(const std::string &filePath, in_port_t port)
{
  dataSendThread = NULL;
  unsigned int i;

  world = new World(this);
  try
    {
      world->loadGame(filePath);
    } catch (std::exception &e)
    {
      std::cout << "errorMap " << e.what() << std::endl;
      return;
    }
  try
    {
      packetFact = new PacketFactory(port);
    } catch (std::exception &f)
    {
      std::cout << "PacketFactory failed creation" << std::endl;
      return;
    }
  players.push_back({"Barbare", -1, false, -1});
  players.push_back({"Mage", -1, false, -1});
  players.push_back({"Valkyrie", -1, false, -1});
  players.push_back({"Elf", -1, false, -1});
  listeners.push_back(new ServConnectListener(this));
  listeners.push_back(new ServSelectPlayerListener(this));
  listeners.push_back(new ServDisconnectListener(this));
  listeners.push_back(new ServControlListener(this));
  listeners.push_back(new ServMapListener(this));
  maxPlayers = 4;
  coPlayers = 0;
  i = 0;
  while (i < listeners.size())
    {
      packetFact->registerListener(listeners[i]);
      ++i;
    }
  listenThread = new std::thread(std::bind(&PacketFactory::recv, std::ref(*packetFact)));
  world->gameLoop();
  packetFact->stop(true);
}

GameServer::~GameServer()
{
  if (dataSendThread)
    dataSendThread->join();
}

void                GameServer::connectAnswer(
	const network::PacketConnect *packet)
{
  connectTmp.push_back(packet->getSocketId());
  sendHandShake(packet->getSocketId());
}

void                GameServer::selectPlayerAnswer(
	const network::PacketSelectPlayer *packet)
{
  bool check;
  int nbrChoose;
  int iTaken;
  unsigned int i;
  int id;

  dataSendMutex.lock();
  i = 0;
  nbrChoose = -1;
  while (i < connectTmp.size())
    {
      if (connectTmp[i] == packet->getSocketId())
	{
	  nbrChoose = 0;
	  break;
	}
      ++i;
    }
  if (nbrChoose == -1)
    {
      sendDeco(packet->getSocketId(),
	       "Error : you are not connect on the server, you must authentificate yourself.");
      return;
    }
  if (packet->getWarrior() == true)
    {
      nbrChoose++;
      iTaken = PlayerChar::BARBARIAN;
    }
  else
    if (packet->getWizard() == true)
      {
	nbrChoose++;
	iTaken = PlayerChar::MAGE;
      }
    else
      if (packet->getValkyrie() == true)
	{
	  nbrChoose++;
	  iTaken = PlayerChar::VALKYRIE;
	}
      else
	if (packet->getElf() == true)
	  {
	    nbrChoose++;
	    iTaken = PlayerChar::RANGER;
	  }
  if (nbrChoose == 1 && players[iTaken].isTake == false)
    {
      players[iTaken].isTake = true;
      players[iTaken].socketId = packet->getSocketId();
      connectTmp.erase(connectTmp.begin() + i);
      try
	{
	  id = world->addNewBody(world->getSpawnPoint().first,
				 world->getSpawnPoint().second,
				 players[iTaken].name, 0);
	} catch (std::exception &e)
	{
	  exit(0);
	}
      players[iTaken].idPlayer = id;
      PacketStartGame myPacket(id);
      packetFact->send(myPacket, packet->getSocketId());
      dataSendThread = new std::thread(
	      std::bind(&GameServer::sendDatas, std::ref(*this),
			packet->getSocketId()));
      coPlayers++;
    }
  else
    sendHandShake(packet->getSocketId());
  dataSendMutex.unlock();
}

void                        GameServer::sendDatas(int socketId)
{
  std::list<ABody *> bodys;
  std::vector<effectGlobal *> effectTab;
  std::vector<soundGlobal *> soundTab;
  std::list<ABody *>::iterator it1;
  unsigned int i;
  PacketMap packetMap(0, world->getMapNames());
  ABody		*body;


  bodys = world->getBodysByCopy();
  soundTab = world->getSoundByCopy();
  effectTab = world->getEffectByCopy();
  it1 = bodys.begin();
  packetFact->send(packetMap, socketId);
  i = 0;
  while (i < players.size())
    {
      if (players[i].idPlayer != -1)
	{
	  body = world->getBodyById(players[i].idPlayer);
	  sendAddEntity(body);
	}
      ++i;
    }
  while (it1 != bodys.end())
    {
      network::PacketAddEntity packet((*it1)->getEntityId(),
				      (*it1)->getTextureId(),
				      (*it1)->getMeshId(),
				      static_cast<int>((*it1)->getPos().first),
				      static_cast<int>((*it1)->getPos().second),
				      (*it1)->getOrientation());
      packetFact->send(packet, socketId);
      it1++;
    }
  i = 0;
  while (i < soundTab.size())
    {
      if (soundTab[i]->loop == true)
	sendSound(soundTab[i]->soundId, soundTab[i]->Id, true,
		  soundTab[i]->pos);
      ++i;
    }
  i = 0;
  while (i < effectTab.size())
    {
      sendEffect(effectTab[i]->effectId, effectTab[i]->Id,
		 effectTab[i]->orientation,
		 effectTab[i]->pos, effectTab[i]->decayTime);
      ++i;
    }
}

void                        GameServer::notifyTake()
{
  PacketHandshake packet(!players[PlayerChar::BARBARIAN].isTake,
			 !players[PlayerChar::MAGE].isTake,
			 !players[PlayerChar::VALKYRIE].isTake,
			 !players[PlayerChar::RANGER].isTake,
			 maxPlayers, coPlayers);
  unsigned int i;

  i = 0;
  while (i < connectTmp.size())
    {
      packetFact->send(packet, connectTmp[i]);
      ++i;
    }
}

void			GameServer::receiveSaveGame(const network::PacketMap *packet)
{
  world->saveGame(packet->getFilename());
}

void                GameServer::receiveDeco(
	const network::PacketDisconnect *packet)
{
  int socketId;
  unsigned int i;

  dataSendMutex.lock();
  socketId = packet->getSocketId();
  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId == socketId)
	{
	  players[i].socketId = -1;
	  world->deleteId(players[i].idPlayer, true);
	  players[i].name = "";
	  players[i].isTake = false;
	  players[i].idPlayer = -1;
	    coPlayers--;
	}
      ++i;
    }
  i = 0;
  while (i < connectTmp.size())
    {
      if (connectTmp[i] == socketId)
	{
	  connectTmp.erase(connectTmp.begin() + i);
	}
      ++i;
    }
  if (getNbrPlayer() == 0)
    {
      packetFact->stop(false);
      delete packetFact;
    }
  dataSendMutex.unlock();
}

void                        GameServer::sendHandShake(int socketFd)
{
  PacketHandshake packet(!players[PlayerChar::BARBARIAN].isTake,
			 !players[PlayerChar::MAGE].isTake,
			 !players[PlayerChar::VALKYRIE].isTake,
			 !players[PlayerChar::RANGER].isTake, maxPlayers,
			 coPlayers);

  packetFact->send(packet, socketFd);
}

void                GameServer::sendDeco(int socketId, const std::string &msg)
{
  PacketDisconnect packet(msg, socketId);

  packetFact->send(packet, socketId);
}

void                GameServer::decoAll(const std::string &msg)
{
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	sendDeco(players[i].socketId, msg);
      ++i;
    }
  i = 0;
  while (i < connectTmp.size())
    {
      sendDeco(connectTmp[i],
	       "You have been disconnected by the server before your total login");
      ++i;
    }
}

void                GameServer::sendAddEntity(ABody *body)
{
  unsigned int i;
  network::PacketAddEntity packet(body->getEntityId(), body->getTextureId(),
				  body->getMeshId(),
				  static_cast<int>(body->getPos().first),
				  static_cast<int>(body->getPos().second),
				  body->getOrientation());

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void                GameServer::sendMoveId(ABody *body)
{
  network::PacketMoveEntity packet(body->getEntityId(),
				   body->getPos().first,
				   body->getPos().second,
				   body->getOrientation());
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void                GameServer::controlInput(const network::PacketControl *packet)
{
  unsigned int i;
  ABody *body;

  dataSendMutex.lock();
  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	if (packet->getSocketId() == players[i].socketId)
	break;
      ++i;
    }
  if ((body = world->getBodyById(players[i].idPlayer)) == NULL)
    return ;
  if (players[i].socketId != -1)
    world->applyCommand(packet->getAngle(), players[i].idPlayer,
			static_cast<core::Command>(packet->getCmd()));
  dataSendMutex.unlock();
}

void                GameServer::sendEffect(unsigned int effect, int id,
					   short orient,
					   const std::pair<double, double> &pos,
					   int decayTime)
{
  PacketAddParticle packet(effect, id, pos.first,
			   pos.second, orient,
			   decayTime);
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void                GameServer::sendStopEffect(int id)
{
  PacketDeleteParticle packet(id);
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void                GameServer::sendStopSound(int id)
{
  PacketStopSound packet(id);
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void                GameServer::sendSound(unsigned int soundId, int id,
					  bool loop,
					  const std::pair<double, double> &pos)
{
  PacketPlaySound packet(soundId, id, pos.first,
			 pos.second, loop);
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void                GameServer::animeEntity(int id, unsigned int idAnime,
					    bool loop)
{
  PacketAnimation packet(id, idAnime, loop);
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

unsigned char        GameServer::getNbrPlayer() const
{
  return (coPlayers);
}

void                GameServer::sendDeleteEntity(ABody *body)
{
  PacketDeleteEntity packet(body->getId());
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId != -1)
	{
	  packetFact->send(packet, players[i].socketId);
	}
      ++i;
    }
}

const std::vector<playerServerData> &GameServer::getPlayers() const
{
  return (players);
}

void                                GameServer::sendHUD(int playerId,
							int health)
{
  PacketHUD packet(health);
  unsigned int i;

  i = 0;
  while (i < players.size())
    {
      if (players[i].idPlayer == playerId)
	{
	  if (players[i].socketId != -1)
	    packetFact->send(packet);
	  break;
	}
      ++i;
    }
}
