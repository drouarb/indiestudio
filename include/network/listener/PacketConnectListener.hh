//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETCONNECTLISTENER_HH
#define GAUNTLET_PACKETCONNECTLISTENER_HH

#include <network/packet/PacketConnect.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketConnectListener: public PacketListener {
        protected:
            PacketConnectListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketConnect *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETCONNECTLISTENER_HH
