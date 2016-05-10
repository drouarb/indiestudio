//
// Created by drouar_b on 5/9/16.
//

#include "network/listener/PacketListener.hh"

gauntlet::network::PacketListener::PacketListener(gauntlet::network::PacketId id): packetId(id) {

}

gauntlet::network::PacketId gauntlet::network::PacketListener::getPacketId() const {
    return packetId;
}