//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <assert.h>
#include "network/packet/PacketDisconnect.hh"

int main() {
    s_socketData data;
    std::cout << "Testing PacketDisconnect" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    gauntlet::network::PacketDisconnect packetDisconnect("testString");

    data.data = packetDisconnect.serialize();

    gauntlet::network::PacketDisconnect packetDisconnect1(data);
    assert(packetDisconnect.getPacketId() == packetDisconnect1.getPacketId());
    assert(packetDisconnect.getMessage() == packetDisconnect1.getMessage());
}