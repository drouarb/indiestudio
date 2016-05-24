#include "ListenerAddEntity.hh"
#include "Core.hh"

gauntlet::core::ListenerAddEntity::ListenerAddEntity(Core & core) : core(core)
{ }

gauntlet::core::ListenerAddEntity::~ListenerAddEntity()
{ }

void
gauntlet::core::ListenerAddEntity::notify(const network::PacketAddEntity * packet)
{
  std::cout << "# add entity" << std::endl;
  core.actionlists.pushAddEntity(packet);
}
