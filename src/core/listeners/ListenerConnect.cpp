#include "ListenerConnect.hh"

gauntlet::core::ListenerConnect::ListenerConnect(Core & core) : core(core)
{ }

gauntlet::core::ListenerConnect::~ListenerConnect()
{ }

void
gauntlet::core::ListenerConnect::notify(const network::PacketConnect * packet)
{
  
}
