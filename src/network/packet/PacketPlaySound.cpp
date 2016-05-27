//
// Created by drouar_b on 5/25/16.
//

#include "PacketPlaySound.hh"

gauntlet::network::PacketPlaySound::PacketPlaySound(s_socketData data) :
        Packet(gauntlet::network::PLAY_SOUND, data.fd) {
    this->deserialize(data.data);
}

gauntlet::network::PacketPlaySound::PacketPlaySound(unsigned int soundId, unsigned int refId, double x, double y,
                                                    bool loop) :
        Packet(gauntlet::network::PLAY_SOUND, -1),
        soundId(soundId),
        refId(refId),
        x(x),
        y(y),
        loop(loop) { }

t_rawdata *gauntlet::network::PacketPlaySound::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetPlaySoundData), 0);
    s_packetPlaySoundData *packetPlaySoundData = reinterpret_cast<s_packetPlaySoundData *>(&data->front());
    packetPlaySoundData->packetId = getPacketId();
    packetPlaySoundData->soundId = soundId;
    packetPlaySoundData->refId = refId;
    packetPlaySoundData->x = x;
    packetPlaySoundData->y = y;
    packetPlaySoundData->loop = (char) (loop ? 1 : 0);
    return data;
}

void gauntlet::network::PacketPlaySound::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetPlaySoundData))
        throw std::logic_error("PacketPlaySound::Invalid data");
    if (data->at(0) != gauntlet::network::PLAY_SOUND) {
        throw std::logic_error("PacketPlaySound::Invalid packet id");
    }
    s_packetPlaySoundData *packetPlaySoundData = reinterpret_cast<s_packetPlaySoundData *>(&data->front());
    soundId = packetPlaySoundData->soundId;
    refId = packetPlaySoundData->refId;
    x = packetPlaySoundData->x;
    y = packetPlaySoundData->y;
    loop = (packetPlaySoundData->loop != 0);
}

size_t gauntlet::network::PacketPlaySound::getPacketSize() const {
    return sizeof(s_packetPlaySoundData);
}


unsigned int gauntlet::network::PacketPlaySound::getSoundId() const {
    return soundId;
}

unsigned int gauntlet::network::PacketPlaySound::getRefId() const {
    return refId;
}

double gauntlet::network::PacketPlaySound::getY() const {
    return y;
}

double gauntlet::network::PacketPlaySound::getX() const {
    return x;
}

bool gauntlet::network::PacketPlaySound::getLoop() const {
    return loop;
}
