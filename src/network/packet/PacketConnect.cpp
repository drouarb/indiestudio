//
// Created by drouar_b on 5/9/16.
//

#include <stdexcept>
#include "network/packet/PacketConnect.hh"

gauntlet::network::PacketConnect::PacketConnect() :
        Packet(gauntlet::network::CONNECT, -1),
        protocolVersion(PROTOCOL_VERSION)
{ }

gauntlet::network::PacketConnect::PacketConnect(const s_socketData &data) :
        Packet(gauntlet::network::CONNECT, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketConnect::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetConnectData), 0);
    s_packetConnectData *packetConnectData = reinterpret_cast<s_packetConnectData *>(&data->front());
    packetConnectData->packetId = this->getPacketId();
    packetConnectData->protocolVersion = PROTOCOL_VERSION;
    return data;
}

void gauntlet::network::PacketConnect::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetConnectData))
        throw std::logic_error("PacketConnect::Invalid data");
    if (data->at(0) != gauntlet::network::CONNECT) {
        throw std::logic_error("PacketConnect::Invalid packet id");
    }
    s_packetConnectData *packetConnectData = reinterpret_cast<s_packetConnectData *>(&data->front());
    this->protocolVersion = packetConnectData->protocolVersion;
}

unsigned int gauntlet::network::PacketConnect::getProtocolVersion() const {
    return protocolVersion;
}

size_t gauntlet::network::PacketConnect::getPacketSize() const {
    return sizeof(s_packetConnectData);
}
