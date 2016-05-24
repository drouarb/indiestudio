//
// ServSelectPlayerListenet.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May 23 17:40:37 2016 Alexis Trouve
// Last update Mon May 23 21:43:37 2016 Alexis Trouve
//

#ifndef SERVSELECT_HH_
# define SERVSELECT_HH_

#include "PacketSelectPlayerListener.hh"
#include "PacketSelectPlayer.hh"
#include "GameServer.hh"

namespace gauntlet
{
  namespace world
  {
    class	ServSelectPlayerListener : public network::PacketSelectPlayerListener
    {
    private:
      GameServer	*gameServer;
    public:
      ServSelectPlayerListener(GameServer *gameserv);
      ~ServSelectPlayerListener();

      virtual void notify(const network::PacketSelectPlayer *packet);
    };
  };
};

#endif
