//
// Created by drouar_b on 5/22/16.
//

#include <iostream>
#include <network/packet/PacketMoveEntity.hh>
#include <assert.h>


int main() {
    s_socketData data;
    std::cout << "Testing PacketMoveEntity" << std::endl;
    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketMoveEntity packetMoveEntity(rand(), rand(), rand(), rand());

    data.data = packetMoveEntity.serialize();

    gauntlet::network::PacketMoveEntity packetMoveEntity1(data);
    assert(packetMoveEntity.getPacketId() == packetMoveEntity1.getPacketId());
    assert(packetMoveEntity.getEntityId() == packetMoveEntity1.getEntityId());
    assert(packetMoveEntity.getX() == packetMoveEntity1.getX());
    assert(packetMoveEntity.getY() == packetMoveEntity1.getY());
    assert(packetMoveEntity.getAngle() == packetMoveEntity1.getAngle());
}