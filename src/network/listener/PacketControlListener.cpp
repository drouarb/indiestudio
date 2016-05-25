//
// Created by drouar_b on 5/25/16.
//

#include "PacketControlListener.hh"

gauntlet::network::PacketControlListener::PacketControlListener():
        PacketListener(gauntlet::network::PACKET_CONTROL)
{ }

void gauntlet::network::PacketControlListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketControl *>(packet));
    }
}



