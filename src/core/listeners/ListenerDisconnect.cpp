#include "ListenerDisconnect.hh"
#include "Core.hh"

gauntlet::core::ListenerDisconnect::ListenerDisconnect(Core &core) : core(core)
{ }

gauntlet::core::ListenerDisconnect::~ListenerDisconnect()
{ }

void
gauntlet::core::ListenerDisconnect::notify(const network::PacketDisconnect *packet)
{
    std::cout << "# notify a" << std::endl;
    core.destroyPacketf(true);
    std::cout << "# notify b" << std::endl;
    core.actionlists.pushDisconnect(packet);
    std::cout << "# notify c" << std::endl;
}
