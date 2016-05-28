//
// GameServer.cpp for GameServer in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:29:03 2016 Alexis Trouve
// Last update Sun May 29 01:00:05 2016 Alexis Trouve
//

#include <iostream>
#include "PlayerChars.hh"
#include "ServSelectPlayerListener.hh"
#include "ServConnectListener.hh"
#include "ServDisconnectListener.hh"
#include "ServControlListener.hh"
#include "GameServer.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

GameServer::GameServer(const std::string& filePath, in_port_t port)
{
  std::cout << "GameServer build" << std::endl;
  unsigned int	i;

  world = new World(this);
  try {
    world->loadGame(filePath);
  } catch (std::runtime_error & e) {
    std::cout << "errorMap " << e.what() << std::endl;
  }
  std::cout << "# world new packetf" << std::endl;
  try {
    packetFact = new PacketFactory(port);
  } catch (std::exception & f) {
    std::cout << "PacketFactory failed creation" << std::endl;
  }
  std::cout << "# world packetf ok" << std::endl;
  players.push_back({"Barbare", -1, false, -1});
  players.push_back({"Mage", -1, false, -1});
  players.push_back({"Valkyrie", -1, false, -1});
  players.push_back({"Elf", -1, false, -1});
  listeners.push_back(new ServConnectListener(this));
  listeners.push_back(new ServSelectPlayerListener(this));
  listeners.push_back(new ServDisconnectListener(this));
  listeners.push_back(new ServControlListener(this));
  maxPlayers = 4;
  coPlayers = 0;
  i = 0;
  while (i < listeners.size())
    {
      packetFact->registerListener(listeners[i]);
      ++i;
    }
  listenThread = new std::thread(&GameServer::listen, std::ref(*this));
  world->gameLoop();
  std::cout << "GameServer build end" << std::endl;
}

GameServer::~GameServer()
{
  //dataSendThread->join();
}

void		GameServer::connectAnswer(const network::PacketConnect *packet)
{
  std::cout << "connectAnswer" << std::endl;
  connectTmp.push_back(packet->getSocketId());
  sendHandShake(packet->getSocketId());
  std::cout << "connectAnswerEnd" << std::endl;
}

void		GameServer::selectPlayerAnswer(const network::PacketSelectPlayer *packet)
{
  std::cout << "selectplayer" << std::endl;
  bool		check;
  int		nbrChoose;
  int		iTaken;
  unsigned int	i;
  int		id;

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
      return ;
    }
  if (packet->getWarrior() == true)
    {
      nbrChoose++;
      iTaken = PlayerChar::BARBARIAN;
    }
  else if (packet->getWizard() == true)
    {
      nbrChoose++;
      iTaken = PlayerChar::MAGE;
    }
  else if (packet->getValkyrie() == true)
    {
      nbrChoose++;
      iTaken = PlayerChar::VALKYRIE;
    }
  else if (packet->getElf() == true)
    {
      nbrChoose++;
      iTaken = PlayerChar::RANGER;
    }
  if (nbrChoose == 1)
    {
      players[iTaken].isTake = true;
      players[iTaken].socketId = packet->getSocketId();
      connectTmp.erase(connectTmp.begin() + i);
      //dataSendMutex.lock();
      PacketStartGame	myPacket((id = world->addNewBody(world->getSpawnPoint().first,
							 world->getSpawnPoint().second,
							 players[iTaken].name, 0)));
      players[iTaken].idPlayer = id;
      packetFact->send(myPacket, packet->getSocketId());
      sendDatas(packet->getSocketId());
      //dataSendThread = new std::thread(std::bind(&GameServer::sendDatas, std::ref(*this), packet->getSocketId()));
      //dataSendMutex.unlock();
    }
  else
    sendHandShake(packet->getSocketId());
  std::cout << "selectplayerend" << std::endl;
}

void			GameServer::sendDatas(int socketId)
{
  std::cout << "sendData" << std::endl;
  std::list<ABody*>	bodys;
  std::vector<effectGlobal*>	effectTab;
  std::vector<soundGlobal*>	soundTab;
  std::list<ABody*>::iterator	it1;
  unsigned int			i;
  PacketMap			packetMap(0, world->getMapNames());

  bodys = world->getBodysByCopy();
  soundTab = world->getSoundByCopy();
  effectTab = world->getEffectByCopy();
  it1 = bodys.begin();
  std::cout << packetMap.getFilename() << std::endl;
  packetFact->send(packetMap, socketId);
  while (it1 != bodys.end())
    {
      network::PacketAddEntity	packet((*it1)->getEntityId(), (*it1)->getTextureId(),
				       (*it1)->getMeshId(), static_cast<int>((*it1)->getPos().first),
				       static_cast<int>((*it1)->getPos().second), (*it1)->getOrientation());
      packetFact->send(packet, socketId);
      it1++;
    }
  i = 0;
  while (i < soundTab.size())
    {
      if (soundTab[i]->loop == true)
	sendSound(soundTab[i]->soundId, soundTab[i]->Id, true, soundTab[i]->pos);
      ++i;
    }
  i = 0;
  while (i < effectTab.size())
    {
      sendEffect(effectTab[i]->effectId, effectTab[i]->Id, effectTab[i]->orientation,
		 effectTab[i]->pos, effectTab[i]->decayTime);
      ++i;
    }
  std::cout << "sendData end" << std::endl;
}

void			GameServer::notifyTake()
{
  std::cout << "notifyTake" << std::endl;
  PacketHandshake	packet(players[PlayerChar::BARBARIAN].isTake, players[PlayerChar::MAGE].isTake,
			       players[PlayerChar::VALKYRIE].isTake, players[PlayerChar::RANGER].isTake,
			       maxPlayers, coPlayers);
  unsigned int		i;

  i = 0;
  while (i < connectTmp.size())
    {
      packetFact->send(packet, connectTmp[i]);
      ++i;
    }
  std::cout << "notifyTakeEnd" << std::endl;
}

void		GameServer::receiveDeco(const network::PacketDisconnect *packet)
{
  std::cout << "receiveDeco" << std::endl;
  int		socketId;
  unsigned int	i;

  socketId = packet->getSocketId();
  i = 0;
  while (i < players.size())
    {
      if (players[i].socketId == socketId)
	{
	  players[i].socketId = -1;
	  players[i].isTake = false;
	}
      ++i;
    }
  i = 0;
  while (i < connectTmp.size())
    {
      if (connectTmp[i] == socketId)
	connectTmp.erase(connectTmp.begin() + i);
      ++i;
    }
  std::cout << "receiveDecoEnd" << std::endl;
}

void			GameServer::sendHandShake(int socketFd)
{
  std::cout << "sendHandShake" << std::endl;
  PacketHandshake	packet(players[PlayerChar::BARBARIAN].isTake, players[PlayerChar::MAGE].isTake,
			       players[PlayerChar::VALKYRIE].isTake, players[PlayerChar::RANGER].isTake, maxPlayers, coPlayers);

  packetFact->send(packet, socketFd);
  std::cout << "sendHandShakeEnd" << std::endl;
}

void		GameServer::sendDeco(int socketId, const std::string& msg)
{
  std::cout << "sendDeco" << std::endl;
  PacketDisconnect	packet(msg, socketId);

  packetFact->send(packet, socketId);
  std::cout << "sendDecoEnd" << std::endl;
}

void		GameServer::decoAll(const std::string& msg)
{
  std::cout << "DecoAll" << std::endl;
  unsigned int		i;

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
      sendDeco(connectTmp[i], "You have been disconnected by the server before your total login");
      ++i;
    }
  std::cout << "DecoAllEnd" << std::endl;
}

void		GameServer::sendAddEntity(ABody *body)
{
  std::cout << "sendAddEntity" << body->getEntityId() << " " << body->getPos().first << ":" << body->getPos().second << ":" << body->getOrientation() << std::endl;
  unsigned int	i;
  network::PacketAddEntity	packet(body->getEntityId(), body->getTextureId(), body->getMeshId(), static_cast<int>(body->getPos().first), static_cast<int>(body->getPos().second), body->getOrientation());
  std::cout << packet.getEntityId() << std::endl;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
  std::cout << "sendAddEntityEnd" << std::endl;
}

void		GameServer::sendMoveId(ABody *body)
{
  network::PacketMoveEntity	packet(body->getEntityId(), body->getPos().first,
				       body->getPos().second, body->getOrientation());
  unsigned int	i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::controlInput(const network::PacketControl *packet)
{
  unsigned int	i;
  ABody		*body;

  i = 0;
  while (i < players.size())
    {
      if (packet->getSocketId() == players[i].socketId)
	break;
      ++i;
    }
  body = world->getBodyById(players[i].idPlayer);
  body->changeOrientation(packet->getAngle());
  world->applyCommand(players[i].idPlayer, static_cast<core::Command>(packet->getCmd()));
}

void		GameServer::sendEffect(unsigned int effect, int id, short orient,
				       const std::pair<double, double>& pos, int decayTime)
{
  PacketAddParticle	packet(effect, id, pos.first, pos.second, orient, decayTime);
  unsigned int		i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::sendStopEffect(int id)
{
  PacketDeleteParticle	packet(id);
  unsigned int	i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::sendStopSound(int id)
{
  PacketStopSound	packet(id);
  unsigned int		i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::sendSound(unsigned int soundId, int id, bool loop, const std::pair<double, double>& pos)
{
  PacketPlaySound	packet(soundId, id, pos.first, pos.second, loop);
  unsigned int		i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::animeEntity(int id, unsigned int idAnime)
{
  PacketAnimation	packet(id, idAnime);
  unsigned int		i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::listen()
{
  std::cout << "listen" << std::endl;
  while (42)
    {
      std::cout << "server listen" << std::endl;
      packetFact->recv();
    }
  std::cout << "listenEnd" << std::endl;
}

unsigned char	GameServer::getNbrPlayer() const
{
  return (coPlayers);
}

void		GameServer::sendDeleteEntity(ABody *body)
{
  PacketDeleteEntity	packet(body->getId());
  unsigned int		i;

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}
