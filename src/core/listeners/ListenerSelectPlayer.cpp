#include "ListenerSelectPlayer.hh"

gauntlet::core::ListenerSelectPlayer::ListenerSelectPlayer(Core & core) : core(core)
{ }

gauntlet::core::ListenerSelectPlayer::~ListenerSelectPlayer()
{ }

void
gauntlet::core::ListenerSelectPlayer::notify(const network::PacketSelectPlayer * packet)
{
  
}
