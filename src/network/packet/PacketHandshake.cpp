//
// Created by drouar_b on 5/12/16.
//

#include <stdexcept>
#include "network/packet/PacketHandshake.hh"

gauntlet::network::PacketHandshake::PacketHandshake(bool warrior, bool wizard, bool valkyrie, bool elf,
                                                    unsigned char maxPlayers, unsigned char connectedPlayers) :
        Packet(gauntlet::network::HANDSHAKE, -1),
        warrior(warrior),
        wizard(wizard),
        valkyrie(valkyrie),
        elf(elf),
        maxPlayers(maxPlayers),
        connectedPlayers(connectedPlayers)
{ }

gauntlet::network::PacketHandshake::PacketHandshake(const s_socketData &data) :
        Packet(gauntlet::network::HANDSHAKE, data.fd) {
    this->deserialize(data.data);
}

t_rawdata *gauntlet::network::PacketHandshake::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_packetHandshakeData), 0);
    s_packetHandshakeData *packetHandshakeData = reinterpret_cast<s_packetHandshakeData *>(&data->front());
    packetHandshakeData->packetId = this->getPacketId();
    packetHandshakeData->connectedPlayers = connectedPlayers;
    packetHandshakeData->maxPlayers = maxPlayers;
    packetHandshakeData->avaibleCharacters =
            (warrior ?  1 << 0 : 0) |
            (wizard ?   1 << 1 : 0) |
            (valkyrie ? 1 << 2 : 0) |
            (elf ?      1 << 3 : 0);
    return data;
}

void gauntlet::network::PacketHandshake::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_packetHandshakeData))
        throw std::logic_error("PacketHandshake::Invalid data");
    if (data->at(0) != gauntlet::network::HANDSHAKE) {
        throw std::logic_error("PacketHandshake::Invalid packet id");
    }
    s_packetHandshakeData *packetHandshakeData = reinterpret_cast<s_packetHandshakeData *>(&data->front());
    connectedPlayers = packetHandshakeData->connectedPlayers;
    maxPlayers = packetHandshakeData->maxPlayers;
    warrior = static_cast<bool>(packetHandshakeData->avaibleCharacters >> 0 & 0x01);
    wizard = static_cast<bool>(packetHandshakeData->avaibleCharacters >> 1 & 0x01);
    valkyrie = static_cast<bool>(packetHandshakeData->avaibleCharacters >> 2 & 0x01);
    elf = static_cast<bool>(packetHandshakeData->avaibleCharacters >> 3 & 0x01);
}

bool gauntlet::network::PacketHandshake::getWarrior() const {
    return warrior;
}

bool gauntlet::network::PacketHandshake::getWizard() const {
    return wizard;
}

bool gauntlet::network::PacketHandshake::getValkyrie() const {
    return valkyrie;
}

bool gauntlet::network::PacketHandshake::getElf() const {
    return elf;
}

unsigned char gauntlet::network::PacketHandshake::getMaxPlayers() const {
    return maxPlayers;
}

unsigned char gauntlet::network::PacketHandshake::getConnectedPlayers() const {
    return connectedPlayers;
}