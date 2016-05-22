//
// Created by drouar_b on 5/22/16.
//

#include "network/listener/PacketSelectPlayerListener.hh"

gauntlet::network::PacketSelectPlayerListener::PacketSelectPlayerListener() : PacketListener(
        gauntlet::network::PLAYER_SELECT) {

}

void gauntlet::network::PacketSelectPlayerListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketSelectPlayer *>(packet));
    }
}


