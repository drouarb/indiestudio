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
            typedef Packet* (PacketFactory::* createPacketFunc)(t_rawdata* data);
        public:
            PacketFactory(in_port_t port);
            PacketFactory(const std::string& address, in_port_t port);
            ~PacketFactory();

            void send(const Packet &packet);
            void recv();

            void registerListener(PacketListener *listener);
            void unregisterListener(PacketListener *listener);

        private:
            template<typename T>  Packet *createPacket(t_rawdata* data) {
                return new T(data);
            }

        private:
            bool run;
            Socket *socket;
            std::map<PacketId, std::set<PacketListener *>> listeners;

            static const std::map<PacketId, createPacketFunc> createMap;
        };
    }
}


#endif //CPP_INDIE_STUDIO_PACKETFACTORY_HH
