//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETPLAYSOUNDLISTENER_HH
#define GAUNTLET_PACKETPLAYSOUNDLISTENER_HH


#include <network/packet/PacketPlaySound.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketPlaySoundListener: public PacketListener {
        protected:
            PacketPlaySoundListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketPlaySound *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETPLAYSOUNDLISTENER_HH
