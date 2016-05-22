//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETMOVEENTITYLISTENER_HH
#define GAUNTLET_PACKETMOVEENTITYLISTENER_HH


#include <network/packet/PacketMoveEntity.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketMoveEntityListener: public PacketListener {
        protected:
            PacketMoveEntityListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketMoveEntity *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETMOVEENTITYLISTENER_HH
