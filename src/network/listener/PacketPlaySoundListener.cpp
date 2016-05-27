//
// Created by drouar_b on 5/25/16.
//

#include "PacketPlaySoundListener.hh"

gauntlet::network::PacketPlaySoundListener::PacketPlaySoundListener():
        PacketListener(gauntlet::network::PLAY_SOUND)
{ }

void gauntlet::network::PacketPlaySoundListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketPlaySound *>(packet));
    }
}


