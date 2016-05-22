//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketHandshakeListener.hh"

gauntlet::network::PacketHandshakeListener::PacketHandshakeListener(): PacketListener(gauntlet::network::HANDSHAKE) {

}

void gauntlet::network::PacketHandshakeListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketHandshake *>(packet));
    }
}



