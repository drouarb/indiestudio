//
// Created by drouar_b on 5/25/16.
//

#include <network/packet/PacketStopSound.hh>
#include <iostream>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketStopSoundParticle" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketStopSound packetStopSound(rand());
    data.data = packetStopSound.serialize();
    gauntlet::network::PacketStopSound packetStopSound1(data);

    assert(packetStopSound.getPacketId() == packetStopSound1.getPacketId());
    assert(packetStopSound.getSoundId() == packetStopSound1.getSoundId());
}