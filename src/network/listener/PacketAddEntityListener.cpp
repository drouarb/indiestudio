//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketAddEntityListener.hh"

gauntlet::network::PacketAddEntityListener::PacketAddEntityListener(): PacketListener(gauntlet::network::ADD_ENTITY) {

}

void gauntlet::network::PacketAddEntityListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketAddEntity *>(packet));
    }
}


