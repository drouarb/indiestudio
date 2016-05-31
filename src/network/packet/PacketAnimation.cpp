//
// Created by drouar_b on 5/27/16.
//

#include "PacketAnimation.hh"

gauntlet::network::PacketAnimation::PacketAnimation(s_socketData data):
        Packet(gauntlet::network::ANIMATION, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketAnimation::PacketAnimation(unsigned int entityId, unsigned int animationId, bool loop):
        Packet(gauntlet::network::ANIMATION, -1),
        entityId(entityId),
        animationId(animationId),
        loop(loop)
{ }

t_rawdata *gauntlet::network::PacketAnimation::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetAnimationData), 0);
    s_packetAnimationData *packetAnimationData = reinterpret_cast<s_packetAnimationData *>(&data->front());
    packetAnimationData->packetId = this->getPacketId();
    packetAnimationData->entityId = entityId;
    packetAnimationData->animationId = animationId;
    packetAnimationData->loop = (unsigned char)loop;
    return data;
}

void gauntlet::network::PacketAnimation::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetAnimationData))
        throw std::logic_error("PacketAnimation::Invalid data");
    if (data->at(0) != gauntlet::network::ANIMATION) {
        throw std::logic_error("PacketAnimation::Invalid packet id");
    }
    s_packetAnimationData *packetAnimationData = reinterpret_cast<s_packetAnimationData*>(&data->front());
    entityId = packetAnimationData->entityId;
    animationId = packetAnimationData->animationId;
    loop = packetAnimationData->loop;
}

size_t gauntlet::network::PacketAnimation::getPacketSize() const {
    return sizeof(s_packetAnimationData);
}

unsigned int gauntlet::network::PacketAnimation::getEntityId() const {
    return entityId;
}

unsigned int gauntlet::network::PacketAnimation::getAnimationId() const {
    return animationId;
}

bool gauntlet::network::PacketAnimation::isLoop() const {
    return loop;
}