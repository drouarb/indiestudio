//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <network/packet/PacketHandshake.hh>
#include <assert.h>

int main() {
    std::cout << "Testing PacketHandshake" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketHandshake packetHandshake(rand() % 2, rand() % 2, rand() % 2, rand() % 2,
    rand() % 255, rand() % 255);

    t_rawdata *data = packetHandshake.serialize();

    gauntlet::network::PacketHandshake packetHandshake1(data);

    assert(packetHandshake.getPacketId() == packetHandshake1.getPacketId());
    assert(packetHandshake.getConnectedPlayers() == packetHandshake1.getConnectedPlayers());
    assert(packetHandshake.getMaxPlayers() == packetHandshake1.getMaxPlayers());
    assert(packetHandshake.getWarrior() == packetHandshake1.getWarrior());
    assert(packetHandshake.getWizard() == packetHandshake1.getWizard());
    assert(packetHandshake.getValkyrie() == packetHandshake1.getValkyrie());
    assert(packetHandshake.getElf() == packetHandshake1.getElf());
}