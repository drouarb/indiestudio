//
// GameServer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 20:56:05 2016 Alexis Trouve
// Last update Mon May 23 22:07:08 2016 Alexis Trouve
//

#ifndef GAMESERVER_HH_
# define GAMESERVER_HH_

#include <thread>
#include <vector>
#include <string>
#include "PacketFactory.hh"
#include "World.hh"
#include "Packet.hh"
#include "PacketConnect.hh"
#include "PacketSelectPlayer.hh"
#include "PacketHandshake.hh"
#include "PacketDisconnect.hh"
#include "PacketListener.hh"

namespace gauntlet
{
  namespace world
  {
    struct	playerServerData
    {
      std::string	name;
      int		socketId;
      bool		isTake;
    };

    class GameServer
    {
    private:
      World				*world;
      network::PacketFactory		*packetFact;
      unsigned char			maxPlayers;
      unsigned char			coPlayers;
      std::vector<network::PacketListener*>	listeners;
      std::vector<playerServerData>	players;
      std::vector<int>			connectTmp;
      std::thread			*listenThread;
    public:
      GameServer(const std::string& filePath, in_port_t port);
      ~GameServer();

      void		connectAnswer(const network::PacketConnect *packet);
      void		selectPlayerAnswer(const network::PacketSelectPlayer *packet);
      void		receiveDeco(const network::PacketDisconnect *packet);
      void		sendHandShake(int fd);
      void		notifyTake();
      void		sendDeco();
      void		DecoAll();
      void		sendMap();
      void		sendAddEntity(std::pair<double, double> pos, short orienta);
      void		listen();
    };
  };
};

#endif
