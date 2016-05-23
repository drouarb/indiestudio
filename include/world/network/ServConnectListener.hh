//
// ConnectListener.hh for ConnectListener in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 22:00:04 2016 Alexis Trouve
// Last update Mon May 23 21:20:55 2016 Alexis Trouve
//

#ifndef SERV_CONNECTLIST_HH_
# define SERV_CONNECTLIST_HH_

#include "PacketConnectListener.hh"
#include "PacketConnect.hh"
#include "GameServer.hh"

namespace gauntlet
{
  namespace world
  {
    class ServConnectListener : public network::PacketConnectListener
    {
    private:
      GameServer			*gameServer;
    public:
      ServConnectListener(GameServer *ngameserv);
      ~ServConnectListener();
      virtual void	notify(const network::PacketConnect *packet);
    };
  };
};

#endif
