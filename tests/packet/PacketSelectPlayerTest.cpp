//
// Created by drouar_b on 5/16/16.
//

#include <iostream>
#include <network/packet/PacketSelectPlayer.hh>
#include <assert.h>

int main() {
    std::cout << "Testing PacketSelectPlayer" << std::endl;

    std::cout << "->Serialisation/Deserialitation" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketSelectPlayer packetSelectPlayer(rand() % 2, rand() % 2, rand() % 2, rand() % 2);

    t_rawdata *data = packetSelectPlayer.serialize();

    gauntlet::network::PacketSelectPlayer packetSelectPlayer1(data);
    assert(packetSelectPlayer.getPacketId() == packetSelectPlayer1.getPacketId());
    assert(packetSelectPlayer.getWarrior() == packetSelectPlayer1.getWarrior());
    assert(packetSelectPlayer.getWizard() == packetSelectPlayer1.getWizard());
    assert(packetSelectPlayer.getValkyrie() == packetSelectPlayer1.getValkyrie());
    assert(packetSelectPlayer.getElf() == packetSelectPlayer1.getElf());
}