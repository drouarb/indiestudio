#include "ListenerHandshake.hh"
#include "ConnectMenu.hh"

gauntlet::core::ListenerHandshake::ListenerHandshake(Core & core) : core(core)
{ }

gauntlet::core::ListenerHandshake::~ListenerHandshake()
{ }

void
gauntlet::core::ListenerHandshake::notify(const network::PacketHandshake * packet)
{
  if (packet->getConnectedPlayers() < packet->getMaxPlayers())
    ConnectMenu::shakehand(true, true);
}
