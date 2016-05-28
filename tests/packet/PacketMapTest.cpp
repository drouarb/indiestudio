//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <network/packet/PacketMap.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketMap" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketMap packetMap(rand(), "Tanguy l'enlise");

    data.data = packetMap.serialize();

    gauntlet::network::PacketMap packetMap1(data);

    assert(packetMap.getPacketId() == packetMap1.getPacketId());
    assert(packetMap.getMapId() == packetMap1.getMapId());
    assert(packetMap.getFilename() == packetMap1.getFilename());
}