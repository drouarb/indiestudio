//
// Created by drouar_b on 5/24/16.
//

#ifndef GAUNTLET_PACKETSTARTGAMELISTENER_HH
#define GAUNTLET_PACKETSTARTGAMELISTENER_HH


#include <network/packet/PacketStartGame.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketStartGameListener : public PacketListener {
        protected:
            PacketStartGameListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketStartGame *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETSTARTGAMELISTENER_HH
