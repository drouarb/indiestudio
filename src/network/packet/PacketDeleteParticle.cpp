//
// Created by drouar_b on 5/25/16.
//

#include "PacketDeleteParticle.hh"

gauntlet::network::PacketDeleteParticle::PacketDeleteParticle(s_socketData data):
        Packet(gauntlet::network::DELETE_PARTICLE, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketDeleteParticle::PacketDeleteParticle(unsigned int particleId):
        Packet(gauntlet::network::DELETE_PARTICLE, -1),
        particleId(particleId)
{ }

t_rawdata *gauntlet::network::PacketDeleteParticle::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetDeleteParticle), 0);
    s_packetDeleteParticle *packetDeleteParticle = reinterpret_cast<s_packetDeleteParticle*>(&data->front());
    packetDeleteParticle->packetId = this->getPacketId();
    packetDeleteParticle->particleId = particleId;
    return data;
}

void gauntlet::network::PacketDeleteParticle::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetDeleteParticle))
        throw std::logic_error("PacketDeleteParticle::Invalid data");
    if (data->at(0) != gauntlet::network::DELETE_PARTICLE) {
        throw std::logic_error("PacketDeleteParticle::Invalid packet id");
    }
    s_packetDeleteParticle *packetDeleteParticle = reinterpret_cast<s_packetDeleteParticle*>(&data->front());
    particleId = packetDeleteParticle->particleId;
}

size_t gauntlet::network::PacketDeleteParticle::getPacketSize() const {
    return sizeof(s_packetDeleteParticle);
}


unsigned int gauntlet::network::PacketDeleteParticle::getParticleId() const {
    return particleId;
}