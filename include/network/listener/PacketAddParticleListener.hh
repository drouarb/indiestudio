//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETADDPARTICLELISTENER_HH
#define GAUNTLET_PACKETADDPARTICLELISTENER_HH


#include <network/packet/PacketAddParticle.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketAddParticleListener: public PacketListener {
        protected:
            PacketAddParticleListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketAddParticle *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETADDPARTICLELISTENER_HH
