//
// Created by drouar_b on 5/24/16.
//

#include "PacketDeleteEntityListener.hh"

gauntlet::network::PacketDeleteEntityListener::PacketDeleteEntityListener():
        PacketListener(gauntlet::network::DELETE_ENTITY) { }

void gauntlet::network::PacketDeleteEntityListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketDeleteEntity *>(packet));
    }
}
