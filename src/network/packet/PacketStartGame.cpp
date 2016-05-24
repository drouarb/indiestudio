//
// Created by drouar_b on 5/24/16.
//

#include "PacketStartGame.hh"

gauntlet::network::PacketStartGame::PacketStartGame(unsigned int entityId):
        Packet(gauntlet::network::START_GAME, -1),
        entityId(entityId)
{ }

gauntlet::network::PacketStartGame::PacketStartGame(const s_socketData &data):
        Packet(gauntlet::network::START_GAME, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketStartGame::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetStartGameData), 0);
    s_packetStartGameData *packetStartGameData = reinterpret_cast<s_packetStartGameData *>(&data->front());
    packetStartGameData->packetId = this->getPacketId();
    packetStartGameData->entityId = this->entityId;
    return data;
}

void gauntlet::network::PacketStartGame::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetStartGameData))
        throw std::logic_error("PacketStartGame::Invalid data");
    if (data->at(0) != this->getPacketId()) {
        throw std::logic_error("PacketStartGame::Invalid packet id");
    }
    s_packetStartGameData *packetStartGameData = reinterpret_cast<s_packetStartGameData *>(&data->front());
    entityId = packetStartGameData->entityId;
}

unsigned int gauntlet::network::PacketStartGame::getEntityId() const {
    return entityId;
}