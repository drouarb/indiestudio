//
// GameServer.cpp for GameServer in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:29:03 2016 Alexis Trouve
// Last update Tue May 24 12:48:09 2016 Alexis Trouve
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
  world->loadGame(filePath);
  packetFact = new PacketFactory(port);
  std::cout << "-- server port: " << port << std::endl;
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
  world->gameLoop();
}

GameServer::~GameServer()
{
}

void		GameServer::connectAnswer(const network::PacketConnect *packet)
{
  std::cout << "-- server received connect" << std::endl;
  connectTmp.push_back(packet->getSocketId());
  std::cout << "-- server sendHandShake" << std::endl;
  sendHandShake(packet->getSocketId());
}

void		GameServer::selectPlayerAnswer(const network::PacketSelectPlayer *packet)
{
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
    }
  else
    sendHandShake(packet->getSocketId());
}

void			GameServer::notifyTake()
{
  PacketHandshake	*packet;
  unsigned int		i;

  packet = new network::PacketHandshake(players[PlayerChar::BARBARIAN].isTake, players[PlayerChar::MAGE].isTake,
					players[PlayerChar::VALKYRIE].isTake, players[PlayerChar::RANGER].isTake, maxPlayers, coPlayers);
  i = 0;
  while (i < connectTmp.size())
    {
      packetFact->send(*packet, connectTmp[i]);
      ++i;
    }
  delete packet;
}

void		GameServer::receiveDeco(const network::PacketDisconnect *packet)
{
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
}

void			GameServer::sendHandShake(int socketFd)
{
  PacketHandshake	packet(players[PlayerChar::BARBARIAN].isTake, players[PlayerChar::MAGE].isTake,
			       players[PlayerChar::VALKYRIE].isTake, players[PlayerChar::RANGER].isTake, maxPlayers, coPlayers);

  packetFact->send(packet, socketFd);
  std::cout << "-- server handshake ok" << std::endl;
}

void		GameServer::sendDeco(int socketId, const std::string& msg)
{
  PacketDisconnect	packet(msg, socketId);

  packetFact->send(packet, socketId);
}

void		GameServer::DecoAll()
{

}

void		GameServer::sendMap()
{

}

void		GameServer::sendAddEntity(ABody *body)
{
  unsigned int	i;
  network::PacketAddEntity	packet(body->getEntityId(), body->getTextureId(), body->getMeshId(), static_cast<int>(body->getPos().first), static_cast<int>(body->getPos().second), body->getOrientation());

  i = 0;
  while (i < players.size())
    {
      packetFact->send(packet, players[i].socketId);
      ++i;
    }
}

void		GameServer::listen()
{
  while (42)
    {
      std::cout << "-- server listen" << std::endl;
      packetFact->recv();
    }
}
