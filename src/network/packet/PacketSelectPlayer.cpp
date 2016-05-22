//
// Created by drouar_b on 5/16/16.
//

#include <stdexcept>
#include "network/packet/PacketSelectPlayer.hh"

gauntlet::network::PacketSelectPlayer::PacketSelectPlayer(bool warrior, bool wizard, bool valkyrie, bool elf) :
        Packet(gauntlet::network::PLAYER_SELECT, -1),
        warrior(warrior),
        wizard(wizard),
        valkyrie(valkyrie),
        elf(elf) { }

gauntlet::network::PacketSelectPlayer::PacketSelectPlayer(const s_socketData &data) :
        Packet(gauntlet::network::PLAYER_SELECT, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketSelectPlayer::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetSelectPlayerData), 0);
    s_packetSelectPlayerData *packetSelectPlayerData = reinterpret_cast<s_packetSelectPlayerData *>(&data->front());
    packetSelectPlayerData->packetId = this->getPacketId();
    packetSelectPlayerData->selectedCharacters =
            (warrior ?  1 << 0 : 0) |
            (wizard ?   1 << 1 : 0) |
            (valkyrie ? 1 << 2 : 0) |
            (elf ?      1 << 3 : 0);
    return data;
}

void gauntlet::network::PacketSelectPlayer::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetSelectPlayerData))
        throw std::logic_error("PacketSelectPlayer::Invalid data");
    if (data->at(0) != gauntlet::network::PLAYER_SELECT) {
        throw std::logic_error("PacketSelectPlayer::Invalid packet id");
    }
    s_packetSelectPlayerData *packetHandshakeData = reinterpret_cast<s_packetSelectPlayerData *>(&data->front());
    warrior = static_cast<bool>(packetHandshakeData->selectedCharacters >> 0 & 0x01);
    wizard = static_cast<bool>(packetHandshakeData->selectedCharacters >> 1 & 0x01);
    valkyrie = static_cast<bool>(packetHandshakeData->selectedCharacters >> 2 & 0x01);
    elf = static_cast<bool>(packetHandshakeData->selectedCharacters >> 3 & 0x01);
}

bool gauntlet::network::PacketSelectPlayer::getWarrior() const {
    return warrior;
}

bool gauntlet::network::PacketSelectPlayer::getWizard() const {
    return wizard;
}

bool gauntlet::network::PacketSelectPlayer::getValkyrie() const {
    return valkyrie;
}

bool gauntlet::network::PacketSelectPlayer::getElf() const {
    return elf;
}







