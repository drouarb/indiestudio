//
// Created by drouar_b on 5/16/16.
//

#include <stdexcept>
#include <cstring>
#include "network/packet/PacketSelectPlayer.hh"

gauntlet::network::PacketSelectPlayer::PacketSelectPlayer(bool warrior, bool wizard, bool valkyrie, bool elf,
                                                          const std::string &name) :
        Packet(gauntlet::network::PLAYER_SELECT, -1),
        warrior(warrior),
        wizard(wizard),
        valkyrie(valkyrie),
        elf(elf),
        name(name) { }

gauntlet::network::PacketSelectPlayer::PacketSelectPlayer(const s_socketData &data) :
        Packet(gauntlet::network::PLAYER_SELECT, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketSelectPlayer::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetSelectPlayerData) + name.size(), 0);
    s_packetSelectPlayerData *packetSelectPlayerData = reinterpret_cast<s_packetSelectPlayerData *>(&data->front());
    packetSelectPlayerData->packetId = this->getPacketId();
    packetSelectPlayerData->selectedCharacters =
            (warrior ?  1 << 0 : 0) |
            (wizard ?   1 << 1 : 0) |
            (valkyrie ? 1 << 2 : 0) |
            (elf ?      1 << 3 : 0);
    packetSelectPlayerData->namelen = name.size();
    strcpy(&packetSelectPlayerData->namestart, name.c_str());
    return data;
}

void gauntlet::network::PacketSelectPlayer::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetSelectPlayerData))
        throw std::logic_error("PacketSelectPlayer::Invalid data");
    if (data->at(0) != gauntlet::network::PLAYER_SELECT) {
        throw std::logic_error("PacketSelectPlayer::Invalid packet id");
    }
    s_packetSelectPlayerData *packetSelectPlayerData = reinterpret_cast<s_packetSelectPlayerData *>(&data->front());
    if (data->size() < sizeof(s_packetSelectPlayerData) + packetSelectPlayerData->namelen)
        throw std::logic_error("PacketSelectPlayer::Invalid data");
    warrior = static_cast<bool>(packetSelectPlayerData->selectedCharacters >> 0 & 0x01);
    wizard = static_cast<bool>(packetSelectPlayerData->selectedCharacters >> 1 & 0x01);
    valkyrie = static_cast<bool>(packetSelectPlayerData->selectedCharacters >> 2 & 0x01);
    elf = static_cast<bool>(packetSelectPlayerData->selectedCharacters >> 3 & 0x01);
    name.assign(&packetSelectPlayerData->namestart, packetSelectPlayerData->namelen);
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

const std::string &gauntlet::network::PacketSelectPlayer::getName() const {
    return name;
}

size_t gauntlet::network::PacketSelectPlayer::getPacketSize() const {
    return sizeof(s_packetSelectPlayerData) + name.size();
}
