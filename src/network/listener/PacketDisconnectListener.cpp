//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketDisconnectListener.hh"

gauntlet::network::PacketDisconnectListener::PacketDisconnectListener(): PacketListener(gauntlet::network::DISCONNECT) {

}

void gauntlet::network::PacketDisconnectListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketDisconnect *>(packet));
    }
}
