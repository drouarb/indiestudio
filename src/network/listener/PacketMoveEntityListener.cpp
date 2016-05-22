//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketMoveEntityListener.hh"

gauntlet::network::PacketMoveEntityListener::PacketMoveEntityListener() : PacketListener(
        gauntlet::network::MOVE_ENTITY) {

}

void gauntlet::network::PacketMoveEntityListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketMoveEntity *>(packet));
    }
}


