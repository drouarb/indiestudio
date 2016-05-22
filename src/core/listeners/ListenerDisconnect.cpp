#include "ListenerDisconnect.hh"
#include "ConnectMenu.hh"

gauntlet::core::ListenerDisconnect::ListenerDisconnect(Core & core) : core(core)
{ }

gauntlet::core::ListenerDisconnect::~ListenerDisconnect()
{ }

void
gauntlet::core::ListenerDisconnect::notify(const network::PacketDisconnect * packet)
{
  ConnectMenu::disconnect(false, core);
}
