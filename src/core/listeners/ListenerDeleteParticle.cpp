#include "ListenerDeleteParticle.hh"
#include "Core.hh"

gauntlet::core::ListenerDeleteParticle::ListenerDeleteParticle(Core & core) : core(core)
{ }

gauntlet::core::ListenerDeleteParticle::~ListenerDeleteParticle()
{ }

void
gauntlet::core::ListenerDeleteParticle::notify(const network::PacketDeleteParticle * packet)
{
  core.actionlists.pushDeleteParticle(packet);
}
