//
// Created by drouar_b on 5/16/16.
//

#include <cstring>
#include <stdexcept>
#include "network/packet/PacketAddEntity.hh"

gauntlet::network::PacketAddEntity::PacketAddEntity(unsigned int entityId, unsigned int textureId, unsigned int meshId,
                                                    double x, double y, short angle) :
        Packet(gauntlet::network::ADD_ENTITY, -1),
        entityId(entityId),
        textureId(textureId),
        meshId(meshId),
        x(x),
        y(y),
        angle(angle) { }

gauntlet::network::PacketAddEntity::PacketAddEntity(const s_socketData &data) :
        Packet(gauntlet::network::ADD_ENTITY, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketAddEntity::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_PacketAddEntity), 0);
    s_PacketAddEntity *packetAddEntity = reinterpret_cast<s_PacketAddEntity *>(&data->front());
    packetAddEntity->packetId = this->getPacketId();
    packetAddEntity->entityId = entityId;
    packetAddEntity->textureId = textureId;
    packetAddEntity->meshId = meshId;
    packetAddEntity->x = x;
    packetAddEntity->y = y;
    packetAddEntity->angle = angle;
    return data;
}

void gauntlet::network::PacketAddEntity::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_PacketAddEntity))
        throw std::logic_error("PacketAddEntity::Invalid data");
    if (data->at(0) != gauntlet::network::ADD_ENTITY) {
        throw std::logic_error("PacketAddEntity::Invalid packet id");
    }
    s_PacketAddEntity *packetAddEntity = reinterpret_cast<s_PacketAddEntity *>(&data->front());
    entityId = packetAddEntity->entityId;
    textureId = packetAddEntity->textureId;
    meshId = packetAddEntity->meshId;
    x = packetAddEntity->x;
    y = packetAddEntity->y;
    angle = packetAddEntity->angle;
}

unsigned int gauntlet::network::PacketAddEntity::getEntityId() const {
    return entityId;
}

unsigned int gauntlet::network::PacketAddEntity::getTextureId() const {
    return textureId;
}

unsigned int gauntlet::network::PacketAddEntity::getMeshId() const {
    return meshId;
}

double gauntlet::network::PacketAddEntity::getX() const {
    return x;
}

double gauntlet::network::PacketAddEntity::getY() const {
    return y;
}

short gauntlet::network::PacketAddEntity::getAngle() const {
    return angle;
}

size_t gauntlet::network::PacketAddEntity::getPacketSize() const {
    return sizeof(s_PacketAddEntity);
}
