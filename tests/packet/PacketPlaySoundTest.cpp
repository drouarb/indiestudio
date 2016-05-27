//
// Created by drouar_b on 5/25/16.
//

#include <iostream>
#include <network/packet/PacketPlaySound.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketPlaySoundParticle" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketPlaySound packetPlaySound(rand(), rand(), rand(), rand(), rand() % 2);
    data.data = packetPlaySound.serialize();
    gauntlet::network::PacketPlaySound packetPlaySound1(data);
    assert(packetPlaySound.getPacketId() == packetPlaySound1.getPacketId());
    assert(packetPlaySound.getSoundId() == packetPlaySound1.getSoundId());
    assert(packetPlaySound.getRefId() == packetPlaySound1.getRefId());
    assert(packetPlaySound.getLoop() == packetPlaySound1.getLoop());
}
