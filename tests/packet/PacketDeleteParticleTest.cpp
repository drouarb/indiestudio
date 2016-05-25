//
// Created by drouar_b on 5/25/16.
//

#include <iostream>
#include <network/packet/PacketDeleteParticle.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketDeleteParticle" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketDeleteParticle packetDeleteParticle(rand());
    data.data = packetDeleteParticle.serialize();
    gauntlet::network::PacketDeleteParticle packetDeleteParticle1(data);
    assert(packetDeleteParticle.getPacketId() == packetDeleteParticle1.getPacketId());
    assert(packetDeleteParticle.getParticleId() == packetDeleteParticle1.getParticleId());
}