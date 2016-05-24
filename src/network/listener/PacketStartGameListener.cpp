//
// Created by drouar_b on 5/24/16.
//

#include "PacketStartGameListener.hh"

gauntlet::network::PacketStartGameListener::PacketStartGameListener():
        PacketListener(gauntlet::network::START_GAME) { }

void gauntlet::network::PacketStartGameListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketStartGame *>(packet));
    }
}



