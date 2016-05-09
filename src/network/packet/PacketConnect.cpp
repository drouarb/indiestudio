//
// Created by drouar_b on 5/9/16.
//

#include "network/packet/PacketConnect.hh"

gauntlet::network::PacketConnect::PacketConnect(): Packet(gauntlet::network::CONNECT) {

}

void *gauntlet::network::PacketConnect::serialize(size_t &size) const {
    return nullptr;
}

void gauntlet::network::PacketConnect::deserialize(void *data) {

}



