//
// Created by drouar_b on 5/27/16.
//

#ifndef GAUNTLET_PACKETANIMATIONLISTENER_HH
#define GAUNTLET_PACKETANIMATIONLISTENER_HH


#include "PacketListener.hh"
#include "PacketAnimation.hh"

namespace gauntlet {
    namespace network {
        class PacketAnimationListener: public PacketListener {
        protected:
            PacketAnimationListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketAnimation *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETANIMATIONLISTENER_HH
