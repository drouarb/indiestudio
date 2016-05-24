//
// Created by drouar_b on 5/24/16.
//

#include <iostream>
#include <network/packet/PacketDeleteEntity.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketDeleteEntity" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketDeleteEntity packetDeleteEntity(rand());

    data.data = packetDeleteEntity.serialize();

    gauntlet::network::PacketDeleteEntity packetDeleteEntity1(data);
    assert(packetDeleteEntity.getPacketId() == packetDeleteEntity1.getPacketId());
    assert(packetDeleteEntity.getEntityId() == packetDeleteEntity1.getEntityId());
}
