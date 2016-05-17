//
// Created by drouar_b on 5/9/16.
//

#include <network/packet/PacketConnect.hh>
#include <network/packet/PacketDisconnect.hh>
#include <network/packet/PacketHandshake.hh>
#include <network/packet/PacketSelectPlayer.hh>
#include <network/packet/PacketAddPlayer.hh>
#include "network/PacketFactory.hh"

gauntlet::network::PacketFactory::PacketFactory(in_port_t port) :
        run(true),
        socket(new Socket(port)) { }

gauntlet::network::PacketFactory::PacketFactory(const std::string &address, in_port_t port) :
        run(true),
        socket(new Socket(address, port)) { }

gauntlet::network::PacketFactory::~PacketFactory() {
    run = false;
    delete (socket);
}

void gauntlet::network::PacketFactory::registerListener(PacketListener *listener) {
    listeners[listener->getPacketId()].insert(listener);
}

void gauntlet::network::PacketFactory::unregisterListener(PacketListener *listener) {
    if (listeners.find(listener->getPacketId()) == listeners.end())
        return;
    for (std::set<PacketListener *>::iterator l = listeners[listener->getPacketId()].begin();
         l != listeners[listener->getPacketId()].end(); l++) {
        if (listener == *l) {
            listeners[listener->getPacketId()].erase(l);
            if (listeners[listener->getPacketId()].size() == 0)
                listeners.erase(listeners.find(listener->getPacketId()));
            return;
        }
    }
}

void gauntlet::network::PacketFactory::send(const Packet &packet) {
    t_rawdata *data = packet.serialize();
    socket->send(&data->front(), data->size());
    delete (data);
}

void gauntlet::network::PacketFactory::recv() {
    t_rawdata *data;
    PacketId id;
    Packet *packet;

    while (run) {
        data = socket->recv();
        id = static_cast<PacketId>(data->at(0));
        packet = NULL;
        try {
            packet = (this->*createMap.at(id))(data);
        } catch (std::exception) { }
        if (packet) {
            if (listeners.find(packet->getPacketId()) != listeners.end())
                for (std::set<PacketListener *>::iterator it = listeners[id].begin(); it != listeners[id].end(); it++)
                    (*it)->notify(packet);
            delete (packet);
        }
    }
}

const std::map<gauntlet::network::PacketId, gauntlet::network::PacketFactory::createPacketFunc>
        gauntlet::network::PacketFactory::createMap = {
        {CONNECT,       &PacketFactory::createPacket<PacketConnect>},
        {DISCONNECT,    &PacketFactory::createPacket<PacketDisconnect>},
        {HANDSHAKE,     &PacketFactory::createPacket<PacketHandshake>},
        {PLAYER_SELECT, &PacketFactory::createPacket<PacketSelectPlayer>},
        {ADD_PLAYER,    &PacketFactory::createPacket<PacketAddPlayer>}
};

