//
// Created by drouar_b on 5/25/16.
//

#include "PacketAddParticleListener.hh"

gauntlet::network::PacketAddParticleListener::PacketAddParticleListener():
        PacketListener(gauntlet::network::ADD_PARTICLE)
{ }

void gauntlet::network::PacketAddParticleListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketAddParticle *>(packet));
    }
}
