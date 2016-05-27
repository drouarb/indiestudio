#include "ListenerAnimation.hh"
#include "Core.hh"

gauntlet::core::ListenerAnimation::ListenerAnimation(Core & core) : core(core)
{ }

gauntlet::core::ListenerAnimation::~ListenerAnimation()
{ }

void
gauntlet::core::ListenerAnimation::notify(const network::PacketAnimation * packet)
{
  core.actionlists.pushAnimation(packet);
}
