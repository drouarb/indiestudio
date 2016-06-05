//
// ServMapListener.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun Jun  5 12:11:47 2016 Alexis Trouve
// Last update Sun Jun  5 12:17:34 2016 Alexis Trouve
//

#ifndef SERV_MAPLIST_HH_
# define SERV_MAPLIST_HH_

#include "PacketMapListener.hh"
#include "PacketMap.hh"
#include "GameServer.hh"

namespace gauntlet
{
  namespace world
  {
    class ServMapListener : public network::PacketMapListener
    {
    private:
      GameServer		*gameServer;
    public:
      ServMapListener(GameServer *ngameserv);
      ~ServMapListener();
      virtual void		notify(const network::PacketMap *packet);
    };
  };
};

#endif
