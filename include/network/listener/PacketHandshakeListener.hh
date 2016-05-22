//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETHANDSHAKELISTENER_HH
#define GAUNTLET_PACKETHANDSHAKELISTENER_HH


#include <network/packet/PacketHandshake.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketHandshakeListener: public PacketListener {
        protected:
            PacketHandshakeListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketHandshake *packet) = 0;
        };
    }
}


#endif //GAUNTLET_PACKETHANDSHAKELISTENER_HH
