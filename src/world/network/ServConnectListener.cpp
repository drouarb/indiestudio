//
// ServConnectListener.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 22:22:49 2016 Alexis Trouve
// Last update Mon May 23 21:36:56 2016 Alexis Trouve
//

#include "ServConnectListener.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

ServConnectListener::ServConnectListener(GameServer *gameServ)
{
  gameServer = gameServ;
}

ServConnectListener::~ServConnectListener()
{
}

void		ServConnectListener::notify(const network::PacketConnect *packet)
{
  gameServer->connectAnswer(packet);
}
