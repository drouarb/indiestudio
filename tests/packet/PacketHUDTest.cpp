//
// Created by drouar_b on 5/31/16.
//

#include <network/packet/PacketHUD.hh>
#include <iostream>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketHUD" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketHUD packetHUD((unsigned char)rand());
    data.data = packetHUD.serialize();
    gauntlet::network::PacketHUD packetHUD1(data);
    assert(packetHUD.getPacketId() == packetHUD1.getPacketId());
    assert(packetHUD.getHealth() == packetHUD1.getHealth());
}