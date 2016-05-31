//
// GameServer.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 20:56:05 2016 Alexis Trouve
// Last update Tue May 31 16:56:01 2016 Alexis Trouve
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
#include "PacketAddEntity.hh"
#include "PacketStartGame.hh"
#include "PacketMoveEntity.hh"
#include "PacketControl.hh"
#include "PacketAddParticle.hh"
#include "PacketDeleteParticle.hh"
#include "PacketPlaySound.hh"
#include "PacketStopSound.hh"
#include "PacketAnimation.hh"
#include "PacketDeleteEntity.hh"
#include "PacketMap.hh"
#include "ABody.hh"

namespace gauntlet
{
  namespace world
  {
    struct	playerServerData
    {
      std::string	name;
      int		socketId;
      bool		isTake;
      int		idPlayer;
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
      std::thread			*dataSendThread;
      std::mutex			dataSendMutex;
    public:
      GameServer(const std::string& filePath, in_port_t port);
      ~GameServer();

      void		connectAnswer(const network::PacketConnect *packet);
      void		selectPlayerAnswer(const network::PacketSelectPlayer *packet);
      void		receiveDeco(const network::PacketDisconnect *packet);
      void		controlInput(const network::PacketControl *packet);
      void		sendHandShake(int fd);
      void		sendDatas(int socketId);
      void		notifyTake();
      void		sendDeco(int fd, const std::string& msg);
      void		decoAll(const std::string& msg);
      void		sendAddEntity(ABody *body);
      void		sendMoveId(ABody *body);
      void		sendEffect(unsigned int effect, int id, short orient,
				   const std::pair<double, double>& pos, int decayTime);
      void		sendStopEffect(int id);
      void		sendSound(unsigned int soundId, int id, bool loop, const std::pair<double, double>& pos);
      void		sendStopSound(int id);
      void		sendDeleteEntity(ABody *body);
      void		animeEntity(int id, unsigned int idanime, bool loop);
      void		listen();
      unsigned char	getNbrPlayer() const;
    };
  };
};

#endif
