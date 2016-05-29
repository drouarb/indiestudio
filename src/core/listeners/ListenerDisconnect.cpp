#include "ListenerDisconnect.hh"
#include "Core.hh"

gauntlet::core::ListenerDisconnect::ListenerDisconnect(Core & core) : core(core)
{ }

gauntlet::core::ListenerDisconnect::~ListenerDisconnect()
{ }

void
gauntlet::core::ListenerDisconnect::notify(const network::PacketDisconnect * packet)
{
  core.destroyPacketf(true);
  core.actionlists.pushDisconnect(packet);
}
