//
// Created by drouar_b on 5/25/16.
//

#include <iostream>
#include <network/packet/PacketAddParticle.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketAddParticle" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketAddParticle packetAddParticle(rand(), rand(), rand(), rand(), rand());
    data.data = packetAddParticle.serialize();
    gauntlet::network::PacketAddParticle packetAddParticle1(data);
    assert(packetAddParticle.getPacketId() == packetAddParticle1.getPacketId());
    assert(packetAddParticle.getParticleId() == packetAddParticle1.getParticleId());
    assert(packetAddParticle.getRefId() == packetAddParticle1.getRefId());
    assert(packetAddParticle.getX() == packetAddParticle1.getX());
    assert(packetAddParticle.getY() == packetAddParticle1.getY());
    assert(packetAddParticle.getDecayTime() == packetAddParticle1.getDecayTime());
}