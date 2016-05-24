#include "ListenerMoveEntity.hh"
#include "Core.hh"

gauntlet::core::ListenerMoveEntity::ListenerMoveEntity(Core & core) : core(core)
{ }

gauntlet::core::ListenerMoveEntity::~ListenerMoveEntity()
{ }

void
gauntlet::core::ListenerMoveEntity::notify(const network::PacketMoveEntity * packet)
{
  core.actionlists.pushMoveEntity(packet);
}
