//
// Created by drouar_b on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETFACTORY_HH
#define CPP_INDIE_STUDIO_PACKETFACTORY_HH

#include <cstdlib>
#include <string>
#include <map>
#include <set>
#include "network/listener/PacketListener.hh"
#include "network/packet/Packet.hh"
#include "Socket.hh"

namespace gauntlet {
    namespace network {
        class PacketFactory {
            typedef Packet* (PacketFactory::* createPacketFunc)(s_socketData data);
            typedef void (PacketListener::* notifyPacketFunc)(const Packet *packet);
        public:
            PacketFactory(in_port_t port);
            PacketFactory(const std::string& address, in_port_t port);
            ~PacketFactory();

            void send(const Packet &packet);
            void send(const Packet &packet, int fd);
            void recv();
            void stop();

            void registerListener(PacketListener *listener);
            void unregisterListener(PacketListener *listener);

            void disconnectionHandler(int fd);

        private:
            template<typename T>  Packet *createPacket(s_socketData data) {
                return new T(data);
            }

            void notifyPacket(Packet *packet);

        private:
            bool run;
            bool connected;
            Socket *socket;
            std::mutex runlock;
            std::map<PacketId, std::set<PacketListener *>> listeners;
            ISocketDisconnectionListener *disconnectionListener;

            static const std::map<PacketId, notifyPacketFunc> notifyMap;
            static const std::map<PacketId, createPacketFunc> createMap;
        };
    }
}


#endif //CPP_INDIE_STUDIO_PACKETFACTORY_HH
