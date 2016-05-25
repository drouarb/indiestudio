#include "ListenerDeleteEntity.hh"
#include "Core.hh"

gauntlet::core::ListenerDeleteEntity::ListenerDeleteEntity(Core & core) : core(core)
{ }

gauntlet::core::ListenerDeleteEntity::~ListenerDeleteEntity()
{ }

void
gauntlet::core::ListenerDeleteEntity::notify(const network::PacketDeleteEntity * packet)
{
  core.actionlists.pushDeleteEntity(packet);
}
