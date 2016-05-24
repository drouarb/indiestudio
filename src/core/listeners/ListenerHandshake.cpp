#include "ListenerHandshake.hh"
#include "WaitPacket.hh"

gauntlet::core::ListenerHandshake::ListenerHandshake(Core &core) : core(core) { }

gauntlet::core::ListenerHandshake::~ListenerHandshake() { }

void
gauntlet::core::ListenerHandshake::notify(const network::PacketHandshake *packet) {
    WaitPacket::receive(new network::PacketHandshake(packet->getWarrior(), packet->getWizard(), packet->getValkyrie(),
                                                     packet->getElf(), packet->getMaxPlayers(),
                                                     packet->getConnectedPlayers()));
}
