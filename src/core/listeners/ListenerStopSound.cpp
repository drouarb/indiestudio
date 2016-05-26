#include "ListenerStopSound.hh"
#include "Core.hh"

gauntlet::core::ListenerStopSound::ListenerStopSound(Core & core) : core(core)
{ }

gauntlet::core::ListenerStopSound::~ListenerStopSound()
{ }

void
gauntlet::core::ListenerStopSound::notify(const network::PacketStopSound * packet)
{
  core.actionlists.pushStopSound(packet);
}
