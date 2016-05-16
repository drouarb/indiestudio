//
// Created by drouar_b on 5/16/16.
//

#include <cstring>
#include <stdexcept>
#include "network/packet/PacketAddPlayer.hh"

gauntlet::network::PacketAddPlayer::PacketAddPlayer() :
        Packet(gauntlet::network::ADD_PLAYER),
        assetId(0),
        playerName("") { }

gauntlet::network::PacketAddPlayer::PacketAddPlayer(t_rawdata *data) :
        PacketAddPlayer() {
    this->deserialize(data);
}

t_rawdata *gauntlet::network::PacketAddPlayer::serialize() const {
    t_rawdata *data = new t_rawdata;
    data->resize(sizeof(s_PacketAddPlayer) + playerName.size(), 0);
    s_PacketAddPlayer *packetAddPlayer = reinterpret_cast<s_PacketAddPlayer *>(&data->front());
    packetAddPlayer->assetId = assetId;
    packetAddPlayer->namelen = playerName.size();
    strcpy(&packetAddPlayer->namestart, playerName.c_str());
    return data;
}

void gauntlet::network::PacketAddPlayer::deserialize(t_rawdata *data) {
    if (data->size() < sizeof(s_PacketAddPlayer))
        throw std::logic_error("PacketAddPlayer::Invalid data");
    if (data->at(0) != gauntlet::network::DISCONNECT) {
        throw std::logic_error("PacketAddPlayer::Invalid packet id");
    }
    s_PacketAddPlayer *packetAddPlayer = reinterpret_cast<s_PacketAddPlayer *>(&data->front());
    if (data->size() < sizeof(s_PacketAddPlayer) + packetAddPlayer->namelen)
        throw std::logic_error("PacketAddPlayer::Invalid data");
    assetId = packetAddPlayer->assetId;
    playerName.assign(&packetAddPlayer->namestart, packetAddPlayer->namelen);
}

unsigned int gauntlet::network::PacketAddPlayer::getAssetId() const {
    return assetId;
}

const std::string &gauntlet::network::PacketAddPlayer::getPlayerName() const {
    return playerName;
}