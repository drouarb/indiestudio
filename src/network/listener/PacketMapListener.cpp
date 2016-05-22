//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketMapListener.hh"

gauntlet::network::PacketMapListener::PacketMapListener(): PacketListener(gauntlet::network::MAP) {

}

void gauntlet::network::PacketMapListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketMap *>(packet));
    }
}


