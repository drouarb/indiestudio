//
// ServDisconnect.hh for ServDisconnect in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May 23 22:10:47 2016 Alexis Trouve
// Last update Mon May 23 22:20:43 2016 Alexis Trouve
//

#ifndef SELECTDISCO_HH_
# define SELECTDISCO_HH_

#include "PacketDisconnectListener.hh"
#include "PacketDisconnect.hh"
#include "GameServer.hh"

namespace gauntlet
{
  namespace world
  {
    class	ServDisconnectListener : public network::PacketDisconnectListener
    {
    private:
      GameServer	*gameServer;
    public:
      ServDisconnectListener(GameServer *gameserv);
      ~ServDisconnectListener();
      
      virtual void notify(const network::PacketDisconnect *packet);
    };
  };
};

#endif
