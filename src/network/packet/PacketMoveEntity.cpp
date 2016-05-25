//
// Created by drouar_b on 5/22/16.
//

#include "network/packet/PacketMoveEntity.hh"

gauntlet::network::PacketMoveEntity::PacketMoveEntity(s_socketData data) :
        Packet(gauntlet::network::MOVE_ENTITY, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketMoveEntity::PacketMoveEntity(unsigned int entityId, int x, int y, short angle) :
        Packet(gauntlet::network::MOVE_ENTITY, -1),
        entityId(entityId),
        x(x),
        y(y),
        angle(angle) { }

t_rawdata *gauntlet::network::PacketMoveEntity::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetMoveEntityData), 0);
    s_packetMoveEntityData *packetMoveEntityData = reinterpret_cast<s_packetMoveEntityData *>(&data->front());
    packetMoveEntityData->packetId = this->getPacketId();
    packetMoveEntityData->entityId = entityId;
    packetMoveEntityData->x = x;
    packetMoveEntityData->y = y;
    packetMoveEntityData->angle = angle;
    return data;
}

void gauntlet::network::PacketMoveEntity::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetMoveEntityData))
        throw std::logic_error("PacketMoveEntity::Invalid data");
    if (data->at(0) != gauntlet::network::MOVE_ENTITY) {
        throw std::logic_error("PacketMoveEntity::Invalid packet id");
    }
    s_packetMoveEntityData *packetMoveEntityData = reinterpret_cast<s_packetMoveEntityData *>(&data->front());
    entityId = packetMoveEntityData->entityId;
    x = packetMoveEntityData->x;
    y = packetMoveEntityData->y;
    angle = packetMoveEntityData->angle;
}

unsigned int gauntlet::network::PacketMoveEntity::getEntityId() const {
    return entityId;
}

int gauntlet::network::PacketMoveEntity::getX() const {
    return x;
}

int gauntlet::network::PacketMoveEntity::getY() const {
    return y;
}

short gauntlet::network::PacketMoveEntity::getAngle() const {
    return angle;
}

size_t gauntlet::network::PacketMoveEntity::getPacketSize() const {
    return sizeof(s_packetMoveEntityData);
}

