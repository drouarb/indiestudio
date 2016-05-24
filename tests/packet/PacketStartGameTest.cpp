//
// Created by drouar_b on 5/24/16.
//

#include <iostream>
#include <network/packet/PacketStartGame.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketStartGame" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketStartGame packetStartGame(rand());

    data.data = packetStartGame.serialize();

    gauntlet::network::PacketStartGame packetStartGame1(data);
    assert(packetStartGame.getPacketId() == packetStartGame1.getPacketId());
    assert(packetStartGame.getEntityId() == packetStartGame1.getEntityId());
}