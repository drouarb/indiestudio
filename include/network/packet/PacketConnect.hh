//
// Created by drouar_b on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETCONNECT_HH
#define CPP_INDIE_STUDIO_PACKETCONNECT_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketConnect: public Packet {
        public:
            PacketConnect();
            virtual ~PacketConnect() {};

            virtual void *serialize(size_t &size) const;
            virtual void deserialize(void *data);

        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETCONNECT_HH
