//
// Created by drouar_b on 5/25/16.
//

#include "PacketAddParticle.hh"

gauntlet::network::PacketAddParticle::PacketAddParticle(s_socketData data):
        Packet(gauntlet::network::ADD_PARTICLE, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketAddParticle::PacketAddParticle(unsigned int particleId, unsigned int refId, double x, double y,
                                                        short angle, int decayTime):
        Packet(gauntlet::network::ADD_PARTICLE, -1),
        particleId(particleId),
        refId(refId),
        x(x),
        y(y),
        angle(angle),
        decayTime(decayTime)
{ }

t_rawdata *gauntlet::network::PacketAddParticle::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetAddParticle), 0);
    s_packetAddParticle *packetAddParticle = reinterpret_cast<s_packetAddParticle*>(&data->front());
    packetAddParticle->packetId = this->getPacketId();
    packetAddParticle->particleId = particleId;
    packetAddParticle->refId = refId;
    packetAddParticle->x = x;
    packetAddParticle->y = y;
    packetAddParticle->angle = angle;
    packetAddParticle->decayTime = decayTime;
    return data;
}

void gauntlet::network::PacketAddParticle::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetAddParticle))
        throw std::logic_error("PacketAddParticle::Invalid data");
    if (data->at(0) != gauntlet::network::ADD_PARTICLE) {
        throw std::logic_error("PacketAddParticle::Invalid packet id");
    }
    s_packetAddParticle *packetAddParticle = reinterpret_cast<s_packetAddParticle*>(&data->front());
    particleId = packetAddParticle->particleId;
    refId = packetAddParticle->refId;
    x = packetAddParticle->x;
    y = packetAddParticle->y;
    angle = packetAddParticle->angle;
    decayTime = packetAddParticle->decayTime;
}

size_t gauntlet::network::PacketAddParticle::getPacketSize() const {
    return sizeof(s_packetAddParticle);
}


unsigned int gauntlet::network::PacketAddParticle::getParticleId() const {
    return particleId;
}

unsigned int gauntlet::network::PacketAddParticle::getRefId() const {
    return refId;
}

double gauntlet::network::PacketAddParticle::getX() const {
    return x;
}

double gauntlet::network::PacketAddParticle::getY() const {
    return y;
}

int gauntlet::network::PacketAddParticle::getDecayTime() const {
    return decayTime;
}

short gauntlet::network::PacketAddParticle::getAngle() const {
    return angle;
}