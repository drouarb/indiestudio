//
// Created by drouar_b on 5/31/16.
//

#ifndef GAUNTLET_PACKETHUDLISTENER_HH
#define GAUNTLET_PACKETHUDLISTENER_HH

#include <network/packet/PacketHUD.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketHUDListener: public PacketListener {
        protected:
            PacketHUDListener();

        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketHUD *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETHUDLISTENER_HH
