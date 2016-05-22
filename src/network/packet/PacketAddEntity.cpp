//
// Created by drouar_b on 5/16/16.
//

#include <cstring>
#include <stdexcept>
#include "network/packet/PacketAddEntity.hh"

gauntlet::network::PacketAddEntity::PacketAddEntity(unsigned int assetId, unsigned int entityId,
                                                    const std::string &playerName) :
        Packet(gauntlet::network::ADD_ENTITY, -1),
        assetId(assetId),
        entityId(entityId),
        playerName(playerName) { }

gauntlet::network::PacketAddEntity::PacketAddEntity(const s_socketData &data) :
        Packet(gauntlet::network::ADD_ENTITY, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketAddEntity::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_PacketAddEntity) + playerName.size(), 0);
    s_PacketAddEntity *packetAddEntity = reinterpret_cast<s_PacketAddEntity *>(&data->front());
    packetAddEntity->packetId = this->getPacketId();
    packetAddEntity->assetId = assetId;
    packetAddEntity->entityId = entityId;
    packetAddEntity->namelen = playerName.size();
    strcpy(&packetAddEntity->namestart, playerName.c_str());
    return data;
}

void gauntlet::network::PacketAddEntity::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_PacketAddEntity))
        throw std::logic_error("PacketAddEntity::Invalid data");
    if (data->at(0) != gauntlet::network::ADD_ENTITY) {
        throw std::logic_error("PacketAddEntity::Invalid packet id");
    }
    s_PacketAddEntity *packetAddEntity = reinterpret_cast<s_PacketAddEntity *>(&data->front());
    if (data->size() < sizeof(s_PacketAddEntity) + packetAddEntity->namelen)
        throw std::logic_error("PacketAddEntity::Invalid data");
    assetId = packetAddEntity->assetId;
    entityId = packetAddEntity->entityId;
    playerName.assign(&packetAddEntity->namestart, packetAddEntity->namelen);
}

unsigned int gauntlet::network::PacketAddEntity::getAssetId() const {
    return assetId;
}

const std::string &gauntlet::network::PacketAddEntity::getPlayerName() const {
    return playerName;
}

unsigned int gauntlet::network::PacketAddEntity::getEntityId() const {
    return entityId;
}