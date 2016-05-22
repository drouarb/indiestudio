//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketConnectListener.hh"

gauntlet::network::PacketConnectListener::PacketConnectListener(): PacketListener(gauntlet::network::CONNECT) {

}

void gauntlet::network::PacketConnectListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketConnect *>(packet));
    }
}


