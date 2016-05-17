//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <network/packet/PacketAddPlayer.hh>
#include <assert.h>

int main() {
    std::cout << "Testing PacketMap" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketAddPlayer packetAddPlayer(rand(), rand(), "Maurice");

    t_rawdata *data = packetAddPlayer.serialize();

    gauntlet::network::PacketAddPlayer packetAddPlayer1(data);
    assert(packetAddPlayer.getPacketId() == packetAddPlayer1.getPacketId());
    assert(packetAddPlayer.getAssetId() == packetAddPlayer1.getAssetId());
    assert(packetAddPlayer.getEntityId() == packetAddPlayer1.getEntityId());
    assert(packetAddPlayer.getPlayerName() == packetAddPlayer.getPlayerName());
}