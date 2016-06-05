#include "ServMapListener.hh"

using namespace gauntlet;
using namespace world;
using namespace network;

ServMapListener::ServMapListener(GameServer *gameServ)
{
  gameServer = gameServ;
}

ServMapListener::~ServMapListener()
{
}

void            ServMapListener::notify(const network::PacketMap *packet)
{
  gameServer->receiveSaveGame(packet);
}
