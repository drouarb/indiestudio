//
// Created by drouar_b on 5/25/16.
//

#include "PacketStopSound.hh"

gauntlet::network::PacketStopSound::PacketStopSound(s_socketData data):
        Packet(gauntlet::network::STOP_SOUND, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketStopSound::PacketStopSound(unsigned int soundId):
        Packet(gauntlet::network::STOP_SOUND, -1),
        soundId(soundId) { }

t_rawdata *gauntlet::network::PacketStopSound::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetStopSound), 0);
    s_packetStopSound *packetStopSound = reinterpret_cast<s_packetStopSound*>(&data->front());
    packetStopSound->packetId = this->getPacketId();
    packetStopSound->soundId = soundId;
    return data;
}

void gauntlet::network::PacketStopSound::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetStopSound))
        throw std::logic_error("PacketStopSound::Invalid data");
    if (data->at(0) != gauntlet::network::STOP_SOUND) {
        throw std::logic_error("PacketStopSound::Invalid packet id");
    }
    s_packetStopSound *packetStopSound = reinterpret_cast<s_packetStopSound*>(&data->front());
    soundId = packetStopSound->soundId;
}

size_t gauntlet::network::PacketStopSound::getPacketSize() const {
    return sizeof(s_packetStopSound);
}


unsigned int gauntlet::network::PacketStopSound::getSoundId() const {
    return soundId;
}