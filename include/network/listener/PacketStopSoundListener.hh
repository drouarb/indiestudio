//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETSTOPSOUNDLISTENER_HH
#define GAUNTLET_PACKETSTOPSOUNDLISTENER_HH


#include <network/packet/PacketStopSound.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketStopSoundListener: public PacketListener {
        protected:
            PacketStopSoundListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketStopSound *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETSTOPSOUNDLISTENER_HH
