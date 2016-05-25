//
// Created by drouar_b on 5/25/16.
//

#include "PacketDeleteParticleListener.hh"

gauntlet::network::PacketDeleteParticleListener::PacketDeleteParticleListener():
        PacketListener(gauntlet::network::DELETE_PARTICLE)
{ }

void gauntlet::network::PacketDeleteParticleListener::notify(const Packet *packet) {
    if (packet->getPacketId() == this->getPacketId()) {
        this->notify(static_cast<const PacketDeleteParticle *>(packet));
    }
}






