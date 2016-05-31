//
// Created by drouar_b on 5/31/16.
//

#include "PacketHUD.hh"

gauntlet::network::PacketHUD::PacketHUD(s_socketData data):
        Packet(gauntlet::network::HUD, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketHUD::PacketHUD(unsigned char health):
        Packet(gauntlet::network::HUD, -1),
        health(health)
{ }

t_rawdata *gauntlet::network::PacketHUD::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetHUDData), 0);
    s_packetHUDData *packetHUDData = reinterpret_cast<s_packetHUDData *>(&data->front());
    packetHUDData->packetId = this->getPacketId();
    packetHUDData->health = health;
    return data;
}

void gauntlet::network::PacketHUD::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetHUDData))
        throw std::logic_error("PacketHUD::Invalid data");
    if (data->at(0) != gauntlet::network::HUD) {
        throw std::logic_error("PacketHUD::Invalid packet id");
    }
    s_packetHUDData *packetHUDData = reinterpret_cast<s_packetHUDData *>(&data->front());
    health = packetHUDData->health;
}

size_t gauntlet::network::PacketHUD::getPacketSize() const {
    return sizeof(s_packetHUDData);
}


unsigned char gauntlet::network::PacketHUD::getHealth() const {
    return health;
}