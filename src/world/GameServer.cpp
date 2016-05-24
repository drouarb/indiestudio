//
// GameServer.cpp for GameServer in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:29:03 2016 Alexis Trouve
// Last update Tue May 24 14:47:49 2016 Alexis Trouve
//

#include <iostream>
#include "PlayerChars.hh"
#include "ServSelectPlayerListener.hh"
#include "ServConnectListener.hh"
#include "ServDisconnectListener.hh"
#include "GameServer.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

GameServer::GameServer(const std::string& filePath, in_port_t port)
{
  unsigned int	i;

  world = new World(this);
  try {
    world->loadGame(filePath);
  } catch (...) {
    std::cout << "errorMap" << std::endl;
  }
  packetFact = new PacketFactory(port);
  players.push_back({"warrior", -1, false});
  players.push_back({"wizard", -1, false});
  players.push_back({"valkyrie", -1, false});
  players.push_back({"elf", -1, false});
  listeners.push_back(new ServConnectListener(this));
  listeners.push_back(new ServSelectPlayerListener(this));
  listeners.push_back(new ServDisconnectListener(this));
  maxPlayers = 4;
  coPlayers = 0;
  i = 0;
  while (i < listeners.size())
    {
      packetFact->registerListener(listeners[i]);
      ++i;
    }
  listenThread = new std::thread(&GameServer::listen, std::ref(*this));
  //world->gameLoop();
  while (1);
}

GameServer::~GameServer()
{
}

void		GameServer::connectAnswer(const network::PacketConnect *packet)
{
  std::cout << "connectAnswer" << std::endl;
  std::cout << "-- server received connect" << std::endl;
  connectTmp.push_back(packet->getSocketId());
  std::cout << "-- server sendHandShake" << std::endl;
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
      PacketStartGame	myPacket(world->addNewBody(world->getSpawnPoint().first,
						   world->getSpawnPoint().second, packet->getName(), 0));
      packetFact->send(myPacket, packet->getSocketId());
    }
  else
    sendHandShake(packet->getSocketId());
  std::cout << "selectplayerend" << std::endl;
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

void		GameServer::DecoAll()
{
  std::cout << "DecoAll" << std::endl;
  std::cout << "DecoAllEnd" << std::endl;
}

void		GameServer::sendMap()
{
  std::cout << "sendMap" << std::endl;
  std::cout << "sendMaEnd" << std::endl;
}

void		GameServer::sendAddEntity(ABody *body)
{
  std::cout << "sendAddEntity" << std::endl;
  unsigned int	i;
  network::PacketAddEntity	packet(body->getEntityId(), body->getTextureId(), body->getMeshId(), static_cast<int>(body->getPos().first), static_cast<int>(body->getPos().second), body->getOrientation());

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
  std::cout << "sendAddEntityEnd" << std::endl;
}

void		GameServer::listen()
{
  std::cout << "listen" << std::endl;
  while (42)
    {
      std::cout << "-- server listen" << std::endl;
      packetFact->recv();
    }
  std::cout << "listenEnd" << std::endl;
}
