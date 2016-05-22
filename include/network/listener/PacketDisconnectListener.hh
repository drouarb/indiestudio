//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETDISCONNECTLISTENER_HH
#define GAUNTLET_PACKETDISCONNECTLISTENER_HH

#include <network/packet/PacketDisconnect.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketDisconnectListener: public PacketListener {
        protected:
            PacketDisconnectListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketDisconnect *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETDISCONNECTLISTENER_HH
