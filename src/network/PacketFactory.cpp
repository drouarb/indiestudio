//
// Created by drouar_b on 5/9/16.
//

#include <network/packet/PacketConnect.hh>
#include "network/PacketFactory.hh"

gauntlet::network::PacketFactory::PacketFactory(in_port_t port) :
        run(true),
        socket(new Socket(port))
{ }

gauntlet::network::PacketFactory::PacketFactory(const std::string &address, in_port_t port) :
        run(true),
        socket(new Socket(address, port))
{ }

gauntlet::network::PacketFactory::~PacketFactory() {
    run = false;
    delete (socket);
}

void gauntlet::network::PacketFactory::send(const Packet &packet) {
    size_t size;

    size = 0;
    socket->send(packet.serialize(size), size);
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

void gauntlet::network::PacketFactory::recv() {
    void *data;
    PacketId id;
    Packet *packet;

    while (run) {
        data = socket->recv();
        id = static_cast<PacketId *>(data)[0];
        packet = NULL;
        try {
            packet = (this->*createMap.at(id))(data);
        } catch (std::exception) {}
        if (packet) {
            if (listeners.find(packet->getPacketId()) != listeners.end())
                for (std::set<PacketListener *>::iterator it = listeners[id].begin(); it != listeners[id].end(); it++)
                    (*it)->notify(packet);
            delete(packet);
        }
    }
}

gauntlet::network::Packet *gauntlet::network::PacketFactory::createConnectPacket(void *data) {
    Packet *p = new PacketConnect();
    p->deserialize(data);
    return p;
}

const std::map<gauntlet::network::PacketId, gauntlet::network::PacketFactory::createPacketFunc>
        gauntlet::network::PacketFactory::createMap = {
        {CONNECT, &PacketFactory::createConnectPacket}
};

