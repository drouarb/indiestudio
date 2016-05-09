//
// Created by drouar_b on 06/05/16.
//

#include "network/packet/Packet.hh"


gauntlet::network::Packet::Packet(PacketId packetId): packetId(packetId) {

}

gauntlet::network::PacketId gauntlet::network::Packet::getPacketId() const {
    return packetId;
}