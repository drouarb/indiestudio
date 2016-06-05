//
// Created by drouar_b on 5/9/16.
//

#include <network/packet/PacketConnect.hh>
#include <network/packet/PacketDisconnect.hh>
#include <network/packet/PacketHandshake.hh>
#include <network/packet/PacketSelectPlayer.hh>
#include <network/packet/PacketAddEntity.hh>
#include <network/packet/PacketMoveEntity.hh>
#include <network/packet/PacketStartGame.hh>
#include <network/packet/PacketDeleteEntity.hh>
#include <network/packet/PacketAddParticle.hh>
#include <network/packet/PacketDeleteParticle.hh>
#include <network/packet/PacketPlaySound.hh>
#include <network/packet/PacketStopSound.hh>
#include <network/packet/PacketControl.hh>
#include <network/packet/PacketAnimation.hh>
#include <network/packet/PacketMap.hh>
#include <iostream>
#include <network/packet/PacketHUD.hh>
#include "network/PacketFactory.hh"
#include "network/PacketFactorySocketDisconnectionListener.hh"

gauntlet::network::PacketFactory::PacketFactory(unsigned short port) :
        connected(true),
        socket(new Socket(port)) {
    disconnectionListener = new PacketFactorySocketDisconnectionListener(this);
    socket->setDisconnectionListener(disconnectionListener);
}

gauntlet::network::PacketFactory::PacketFactory(const std::string &address, unsigned short port) :
        connected(true),
        socket(new Socket(address, port)) {
    disconnectionListener = new PacketFactorySocketDisconnectionListener(this);
    socket->setDisconnectionListener(disconnectionListener);
}

gauntlet::network::PacketFactory::~PacketFactory() {
    run = false;
    delete (socket);
    delete (disconnectionListener);
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
    socket->send(data);
    delete (data);
}

void gauntlet::network::PacketFactory::send(const Packet &packet, int fd) {
    t_rawdata *data = packet.serialize();
    socket->send(data, fd);
    delete (data);
}

void gauntlet::network::PacketFactory::recv() {
    s_socketData data;
    PacketId id;
    Packet *packet;

    runlock.lock();
    run = true;
    while (run && connected) {
        data = socket->recv();
        while (data.data->size() > 0) {
            id = static_cast<PacketId>(data.data->at(0));
            packet = NULL;
            try {
                packet = (this->*createMap.at(id))(data);
            } catch (std::exception *e) {
                std::cerr << "PacketFactory::Invalid packet " << (int)id << "Received" << std::endl;
		std::err << e->what() << std::endl;
                packet = NULL;
                //data.data->resize(0);
            }
            if (packet) {
                this->notifyPacket(packet);
                for (size_t i = 0; i < packet->getPacketSize() && data.data->size() > 0; i++) {
                    data.data->erase(data.data->begin());
                }
                delete (packet);
            }
        }
        delete (data.data);
    }
    runlock.unlock();
}

void gauntlet::network::PacketFactory::stop(bool wait) {
    run = false;
    socket->unlock();
    if (wait)
    {
        runlock.lock();
        runlock.unlock();
    }
}

void gauntlet::network::PacketFactory::notifyPacket(gauntlet::network::Packet *packet) {
    if (listeners.find(packet->getPacketId()) != listeners.end()) {
        for (std::set<PacketListener *>::iterator it = listeners[packet->getPacketId()].begin();
             it != listeners[packet->getPacketId()].end(); it++) {
            (*it)->notify(packet);
        }
    }
}

void gauntlet::network::PacketFactory::disconnectionHandler(int fd) {
    if (socket->getType() == CLIENT)
        connected = false;
    PacketDisconnect *packet = new PacketDisconnect("Connection lost", fd);
    this->notifyPacket(packet);
}

const std::map<gauntlet::network::PacketId, gauntlet::network::PacketFactory::createPacketFunc>
        gauntlet::network::PacketFactory::createMap = {
        {CONNECT,         &PacketFactory::createPacket<PacketConnect>},
        {DISCONNECT,      &PacketFactory::createPacket<PacketDisconnect>},
        {HANDSHAKE,       &PacketFactory::createPacket<PacketHandshake>},
        {PLAYER_SELECT,   &PacketFactory::createPacket<PacketSelectPlayer>},
        {START_GAME,      &PacketFactory::createPacket<PacketStartGame>},
        {MAP,             &PacketFactory::createPacket<PacketMap>},
        {ADD_ENTITY,      &PacketFactory::createPacket<PacketAddEntity>},
        {MOVE_ENTITY,     &PacketFactory::createPacket<PacketMoveEntity>},
        {DELETE_ENTITY,   &PacketFactory::createPacket<PacketDeleteEntity>},
        {ADD_PARTICLE,    &PacketFactory::createPacket<PacketAddParticle>},
        {DELETE_PARTICLE, &PacketFactory::createPacket<PacketDeleteParticle>},
        {PLAY_SOUND,      &PacketFactory::createPacket<PacketPlaySound>},
        {STOP_SOUND,      &PacketFactory::createPacket<PacketStopSound>},
        {PACKET_CONTROL,  &PacketFactory::createPacket<PacketControl>},
        {ANIMATION,       &PacketFactory::createPacket<PacketAnimation>},
        {HUD,             &PacketFactory::createPacket<PacketHUD>}
};

bool gauntlet::network::PacketFactory::isConnected() const {
    return connected;
}
