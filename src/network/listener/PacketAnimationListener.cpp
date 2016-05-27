//
// Created by drouar_b on 5/27/16.
//

#include "PacketAnimationListener.hh"

gauntlet::network::PacketAnimationListener::PacketAnimationListener():
        PacketListener(gauntlet::network::ANIMATION)
{ }

void gauntlet::network::PacketAnimationListener::notify(const gauntlet::network::Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketAnimation *>(packet));
    }
}


