//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <network/packet/PacketAddEntity.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketAddEntity" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketAddEntity packetAddEntity(rand(), rand(), rand(), rand(), rand(), rand());

    data.data = packetAddEntity.serialize();

    gauntlet::network::PacketAddEntity packetAddEntity1(data);
    assert(packetAddEntity.getPacketId() == packetAddEntity1.getPacketId());
    assert(packetAddEntity.getEntityId() == packetAddEntity1.getEntityId());
    assert(packetAddEntity.getTextureId() == packetAddEntity1.getTextureId());
    assert(packetAddEntity.getMeshId() == packetAddEntity1.getMeshId());
    assert(packetAddEntity.getX() == packetAddEntity1.getX());
    assert(packetAddEntity.getY() == packetAddEntity1.getY());
    assert(packetAddEntity.getAngle() == packetAddEntity1.getAngle());
}