//
// Created by drouar_b on 5/27/16.
//

#include <iostream>
#include <network/packet/PacketAnimation.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketAddEntity" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketAnimation packetAnimation(rand(), rand());
    data.data = packetAnimation.serialize();
    gauntlet::network::PacketAnimation packetAnimation1(data);
    assert(packetAnimation.getPacketId() == packetAnimation1.getPacketId());
    assert(packetAnimation.getEntityId() == packetAnimation1.getEntityId());
    assert(packetAnimation.getAnimationId() == packetAnimation1.getAnimationId());
}