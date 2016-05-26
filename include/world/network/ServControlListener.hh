//
// ServControlListener.hh for Serv in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 26 11:48:07 2016 Alexis Trouve
// Last update Thu May 26 11:54:11 2016 Alexis Trouve
//

#ifndef SERVCONTROL_HH_
#define SERVCONTROL_HH_

#include "PacketControlListener.hh"
#include "PacketControl.hh"
#include "GameServer.hh"

namespace gauntlet
{
  namespace world
  {
    class ServControlListener : public network::PacketControlListener
    {
    private:
      GameServer	*gameServer;
    public:
      ServControlListener(GameServer *gameserv);
      ~ServControlListener();

      virtual void	notify(const network::PacketControl *packet);
    };
  };
};

#endif
