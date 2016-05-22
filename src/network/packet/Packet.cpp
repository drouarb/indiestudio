//
// Created by drouar_b on 06/05/16.
//

#include "network/packet/Packet.hh"


gauntlet::network::Packet::Packet(PacketId packetId, int socketId): packetId(packetId), socketId(socketId) {

}

gauntlet::network::PacketId gauntlet::network::Packet::getPacketId() const {
    return packetId;
}

int gauntlet::network::Packet::getSocketId() const {
    return socketId;
}
