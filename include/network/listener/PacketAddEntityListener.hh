//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETADDENTITYLISTENER_HH
#define GAUNTLET_PACKETADDENTITYLISTENER_HH


#include <network/packet/PacketAddEntity.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketAddEntityListener: public PacketListener {
        protected:
            PacketAddEntityListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketAddEntity *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETADDENTITYLISTENER_HH
