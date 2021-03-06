#include "ListenerMap.hh"
#include "Core.hh"

gauntlet::core::ListenerMap::ListenerMap(Core & core) : core(core)
{ }

gauntlet::core::ListenerMap::~ListenerMap()
{ }

void
gauntlet::core::ListenerMap::notify(const network::PacketMap * packet)
{
  core.actionlists.pushMap(packet);
}
