//
// ServDisconnectListener.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 22:22:49 2016 Alexis Trouve
// Last update Mon May 23 22:21:30 2016 Alexis Trouve
//

#include "ServDisconnectListener.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

ServDisconnectListener::ServDisconnectListener(GameServer *gameServ)
{
  gameServer = gameServ;
}

ServDisconnectListener::~ServDisconnectListener()
{
}

void		ServDisconnectListener::notify(const network::PacketDisconnect *packet)
{
  gameServer->receiveDeco(packet);
}
