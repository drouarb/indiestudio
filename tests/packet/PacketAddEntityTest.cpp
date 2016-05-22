//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <network/packet/PacketAddEntity.hh>
#include <assert.h>

int main() {
    s_socketData data;
    std::cout << "Testing PacketMap" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketAddEntity packetAddEntity(rand(), rand(), "Maurice");

    data.data = packetAddEntity.serialize();

    gauntlet::network::PacketAddEntity packetAddEntity1(data);
    assert(packetAddEntity.getPacketId() == packetAddEntity1.getPacketId());
    assert(packetAddEntity.getAssetId() == packetAddEntity1.getAssetId());
    assert(packetAddEntity.getEntityId() == packetAddEntity1.getEntityId());
    assert(packetAddEntity.getPlayerName() == packetAddEntity.getPlayerName());
}