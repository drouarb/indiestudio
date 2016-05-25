//
// Created by drouar_b on 5/25/16.
//

#include "PacketControlTest.hh"

gauntlet::network::PacketControl::PacketControl(s_socketData data):
        Packet(gauntlet::network::PACKET_CONTROL, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketControl::PacketControl(unsigned char cmd, short angle):
        Packet(gauntlet::network::PACKET_CONTROL, -1),
        cmd(cmd),
        angle(angle)
{ }

t_rawdata *gauntlet::network::PacketControl::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetControlData), 0);
    s_packetControlData *packetControlData = reinterpret_cast<s_packetControlData*>(&data->front());
    packetControlData->packetId = this->getPacketId();
    packetControlData->cmd = cmd;
    packetControlData->angle = angle;
    return data;
}

void gauntlet::network::PacketControl::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetControlData))
        throw std::logic_error("PacketControl::Invalid data");
    if (data->at(0) != gauntlet::network::PACKET_CONTROL) {
        throw std::logic_error("PacketControl::Invalid packet id");
    }
    s_packetControlData *packetControlData = reinterpret_cast<s_packetControlData*>(&data->front());
    cmd = packetControlData->cmd;
    angle = packetControlData->angle;
}

size_t gauntlet::network::PacketControl::getPacketSize() const {
    return sizeof(s_packetControlData);
}


unsigned char gauntlet::network::PacketControl::getCmd() const {
    return cmd;
}

short gauntlet::network::PacketControl::getAngle() const {
    return angle;
}