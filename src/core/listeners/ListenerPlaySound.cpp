#include "ListenerPlaySound.hh"
#include "Core.hh"

gauntlet::core::ListenerPlaySound::ListenerPlaySound(Core & core) : core(core)
{ }

gauntlet::core::ListenerPlaySound::~ListenerPlaySound()
{ }

void
gauntlet::core::ListenerPlaySound::notify(const network::PacketPlaySound * packet)
{
  core.actionlists.pushPlaySound(packet);
}
