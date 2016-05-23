//
// GameServer.cpp for GameServer in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:29:03 2016 Alexis Trouve
// Last update Mon May 23 21:49:22 2016 Alexis Trouve
//

#include "ServSelectPlayerListener.hh"
#include "ServConnectListener.hh"
#include "GameServer.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

GameServer::GameServer(const std::string& filePath, in_port_t port)
{
  world = new World(this);;
  world->loadGame(filePath);
  packetFact = new PacketFactory(port);
  players.push_back({"warrior", -1, false});
  players.push_back({"wizard", -1, false});
  players.push_back({"valkyrie", -1, false});
  players.push_back({"elf", -1, false});
  listeners.push_back(new ServConnectListener(this));
  listeners.push_back(new ServSelectPlayerListener(this));
  maxPlayers = 4;
  coPlayers = 0;
}

GameServer::~GameServer()
{
}

void		GameServer::connectAnswer(const network::PacketConnect *packet)
{
  connectTmp.push_back(packet->getSocketId());
  sendHandShake(packet->getSocketId());
}

void		GameServer::selectPlayerAnswer(const network::PacketSelectPlayer *packet)
{
  bool		check;
  int		nbrChoose;
  int		iTaken;

  nbrChoose = 0;
  coPlayers++;
  if (packet->getWarrior() == true)
    {
      nbrChoose++;
      iTaken = WARRIOR;
    }
  else if (packet->getWizard() == true)
    {
      nbrChoose++;
      iTaken = WIZARD;
    }
  else if (packet->getValkyrie() == true)
    {
      nbrChoose++;
      iTaken = VALKYRIE;
    }
  else if (packet->getElf() == true)
    {
      nbrChoose++;
      iTaken = ELF;
    }
  if (nbrChoose == 1)
    {
      notifyTake();
    }
  else
    notifyTake();
}

void			GameServer::notifyTake()
{
  PacketHandshake	*packet;
  unsigned int		i;

  packet = new network::PacketHandshake(players[WARRIOR].isTake, players[WIZARD].isTake,
					players[VALKYRIE].isTake, players[ELF].isTake, maxPlayers, coPlayers);
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

}

void			GameServer::sendHandShake(int socketFd)
{
  PacketHandshake	*packet;

  packet = new network::PacketHandshake(players[WARRIOR].isTake, players[WIZARD].isTake,
			       players[VALKYRIE].isTake, players[ELF].isTake, maxPlayers, coPlayers);
  packetFact->send(*packet, socketFd);
}

void		GameServer::sendDeco()
{

}

void		GameServer::DecoAll()
{

}

void		GameServer::sendMap()
{

}

void		GameServer::sendAddEntity(std::pair<double, double> pos, short norient)
{
  
}
