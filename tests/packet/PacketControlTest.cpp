//
// Created by drouar_b on 5/25/16.
//

#include <iostream>
#include <network/packet/PacketControlTest.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketStopSoundParticle" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketControl packetControl(rand(), rand());
    data.data = packetControl.serialize();
    gauntlet::network::PacketControl packetControl1(data);
    assert(packetControl.getPacketId() == packetControl1.getPacketId());
    assert(packetControl.getCmd() == packetControl1.getCmd());
    assert(packetControl.getAngle() == packetControl1.getAngle());
}