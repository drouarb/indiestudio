//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <assert.h>
#include "network/packet/PacketConnect.hh"

int main() {
    s_socketData data;
    std::cout << "Testing PacketConnect" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    gauntlet::network::PacketConnect packetConnect;

    data.data = packetConnect.serialize();

    gauntlet::network::PacketConnect packetConnect1(data);
    assert(packetConnect.getPacketId() == packetConnect1.getPacketId());
    assert(packetConnect.getProtocolVersion() == packetConnect1.getProtocolVersion());
}