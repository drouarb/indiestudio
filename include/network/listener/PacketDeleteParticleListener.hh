//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETDELETEPARTICLELISTENER_HH
#define GAUNTLET_PACKETDELETEPARTICLELISTENER_HH

#include <network/packet/PacketDeleteParticle.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketDeleteParticleListener: public PacketListener {
        protected:
            PacketDeleteParticleListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketDeleteParticle *packet) = 0;

        };
    }
}

#endif //GAUNTLET_PACKETDELETEPARTICLELISTENER_HH
