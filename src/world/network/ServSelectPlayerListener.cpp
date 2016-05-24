//
// ServSelectPlayerListener.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Mon May 23 17:45:36 2016 Alexis Trouve
// Last update Mon May 23 21:23:57 2016 Alexis Trouve
//

#include "ServSelectPlayerListener.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

ServSelectPlayerListener::ServSelectPlayerListener(GameServer *gameserv)
{
  gameServer = gameserv;
}

ServSelectPlayerListener::~ServSelectPlayerListener()
{
}

void		ServSelectPlayerListener::notify(const PacketSelectPlayer *packet)
{
  gameServer->selectPlayerAnswer(packet);
}
