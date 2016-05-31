//
// Created by drouar_b on 5/31/16.
//

#include "PacketHUDListener.hh"

gauntlet::network::PacketHUDListener::PacketHUDListener(): PacketListener(gauntlet::network::HUD) {

}

void gauntlet::network::PacketHUDListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketHUD *>(packet));
    }
}


