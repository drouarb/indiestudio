//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETMAPLISTENER_HH
#define GAUNTLET_PACKETMAPLISTENER_HH


#include <network/packet/PacketMap.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketMapListener: public PacketListener {
        protected:
            PacketMapListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketMap *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETMAPLISTENER_HH
