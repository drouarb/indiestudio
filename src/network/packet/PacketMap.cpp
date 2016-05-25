//
// Created by drouar_b on 5/16/16.
//

#include <stdexcept>
#include "network/packet/PacketMap.hh"

gauntlet::network::PacketMap::PacketMap(unsigned int mapId) :
        Packet(gauntlet::network::MAP, -1),
        mapId(mapId) { }

gauntlet::network::PacketMap::PacketMap(const s_socketData &data) :
        Packet(gauntlet::network::MAP, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketMap::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetMapData), 0);
    s_packetMapData *packetMapData = reinterpret_cast<s_packetMapData *>(&data->front());
    packetMapData->packetId = this->getPacketId();
    packetMapData->mapId = mapId;
    return data;
}

void gauntlet::network::PacketMap::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetMapData))
        throw std::logic_error("PacketMap::Invalid data");
    if (data->at(0) != gauntlet::network::MAP) {
        throw std::logic_error("PacketMap::Invalid packet id");
    }
    s_packetMapData *packetMapData = reinterpret_cast<s_packetMapData *>(&data->front());
    mapId = packetMapData->mapId;
}

unsigned int gauntlet::network::PacketMap::getMapId() const {
    return mapId;
}

size_t gauntlet::network::PacketMap::getPacketSize() const {
    return sizeof(s_packetMapData);
}

