#include "ListenerHUD.hh"
#include "Core.hh"

gauntlet::core::ListenerHUD::ListenerHUD(Core & core) : core(core)
{ }

gauntlet::core::ListenerHUD::~ListenerHUD()
{ }

void
gauntlet::core::ListenerHUD::notify(const network::PacketHUD * packet)
{
  core.actionlists.pushHUD(packet);
}
