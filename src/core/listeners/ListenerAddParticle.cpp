#include "ListenerAddParticle.hh"
#include "Core.hh"

gauntlet::core::ListenerAddParticle::ListenerAddParticle(Core & core) : core(core)
{ }

gauntlet::core::ListenerAddParticle::~ListenerAddParticle()
{ }

void
gauntlet::core::ListenerAddParticle::notify(const network::PacketAddParticle * packet)
{
  core.actionlists.pushAddParticle(packet);
}
