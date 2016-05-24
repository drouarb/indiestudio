//
// Created by drouar_b on 5/24/16.
//

#include "PacketDeleteEntity.hh"

gauntlet::network::PacketDeleteEntity::PacketDeleteEntity(unsigned int entityId):
        Packet(gauntlet::network::DELETE_ENTITY, -1),
        entityId(entityId)
{ }

gauntlet::network::PacketDeleteEntity::PacketDeleteEntity(const s_socketData &data):
        Packet(gauntlet::network::DELETE_ENTITY, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketDeleteEntity::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetDeleteEntityData), 0);
    s_packetDeleteEntityData *packetDeleteEntityData = reinterpret_cast<s_packetDeleteEntityData *>(&data->front());
    packetDeleteEntityData->packetId = this->getPacketId();
    packetDeleteEntityData->entityId = this->entityId;
    return data;
}

void gauntlet::network::PacketDeleteEntity::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetDeleteEntityData))
        throw std::logic_error("PacketDeleteEntity::Invalid data");
    if (data->at(0) != this->getPacketId()) {
        throw std::logic_error("PacketDeleteEntity::Invalid packet id");
    }
    s_packetDeleteEntityData *packetDeleteEntityData = reinterpret_cast<s_packetDeleteEntityData *>(&data->front());
    entityId = packetDeleteEntityData->entityId;
}

unsigned int gauntlet::network::PacketDeleteEntity::getEntityId() const {
    return entityId;
}
