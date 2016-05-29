//
// Created by drouar_b on 5/12/16.
//

#include <stdexcept>
#include <cstring>
#include "network/packet/PacketDisconnect.hh"


gauntlet::network::PacketDisconnect::PacketDisconnect(const std::string &message, int fd):
        Packet(gauntlet::network::DISCONNECT, fd),
        message(message)
{ }

gauntlet::network::PacketDisconnect::PacketDisconnect(const s_socketData &data):
        Packet(gauntlet::network::DISCONNECT, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketDisconnect::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetDisconnectData) + message.length(), 0);
    s_packetDisconnectData *packetDisconnectData = reinterpret_cast<s_packetDisconnectData *>(&data->front());
    packetDisconnectData->packetId = this->getPacketId();
    packetDisconnectData->stringsize = static_cast<int>(message.size());
    strcpy(&packetDisconnectData->stringstart, message.c_str());
    return data;
}

void gauntlet::network::PacketDisconnect::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetDisconnectData))
        throw std::logic_error("PacketDisconnect::Invalid data");
    if (data->at(0) != gauntlet::network::DISCONNECT) {
        throw std::logic_error("PacketDisconnect::Invalid packet id");
    }
    s_packetDisconnectData *packetDisconnectData = reinterpret_cast<s_packetDisconnectData *>(&data->front());
    if (data->size() < sizeof(s_packetDisconnectData) + packetDisconnectData->stringsize) {
        throw std::logic_error("PacketDisconnect::Invalid data");
    }
    message.assign(&packetDisconnectData->stringstart, packetDisconnectData->stringsize);
}

const std::string &gauntlet::network::PacketDisconnect::getMessage() const {
    return message;
}

size_t gauntlet::network::PacketDisconnect::getPacketSize() const {
    return sizeof(s_packetDisconnectData) + message.size();
}
