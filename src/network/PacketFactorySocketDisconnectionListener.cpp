//
// Created by drouar_b on 5/22/16.
//

#include "network/PacketFactorySocketDisconnectionListener.hh"

gauntlet::network::PacketFactorySocketDisconnectionListener::PacketFactorySocketDisconnectionListener(
        PacketFactory *pf): factory(pf) { }

void gauntlet::network::PacketFactorySocketDisconnectionListener::notify(int fd) {
    factory->disconnectionHandler(fd);
}



