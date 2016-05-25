//
// Created by drouar_b on 5/25/16.
//

#include "PacketStopSoundListener.hh"

gauntlet::network::PacketStopSoundListener::PacketStopSoundListener():
        PacketListener(gauntlet::network::STOP_SOUND)
{ }

void gauntlet::network::PacketStopSoundListener::notify(const gauntlet::network::Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketStopSound *>(packet));
    }
}



