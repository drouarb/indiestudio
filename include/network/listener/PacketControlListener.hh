//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETCONTROLLISTENER_HH
#define GAUNTLET_PACKETCONTROLLISTENER_HH


#include <network/packet/PacketControl.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketControlListener: public PacketListener {
        protected:
            PacketControlListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketControl *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETCONTROLLISTENER_HH
