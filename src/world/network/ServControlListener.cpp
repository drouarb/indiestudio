//
// ServControlListener.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Thu May 26 12:13:36 2016 Alexis Trouve
// Last update Thu May 26 13:28:17 2016 Alexis Trouve
//

#include "ServControlListener.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

ServControlListener::ServControlListener(GameServer *gameServ)
{
  gameServer = gameServ;
}

ServControlListener::~ServControlListener()
{

}

void		ServControlListener::notify(const network::PacketControl *packet)
{
  gameServer->controlInput(packet);
}
