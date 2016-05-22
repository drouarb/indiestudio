//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETSELECTPLAYERLISTENER_HH
#define GAUNTLET_PACKETSELECTPLAYERLISTENER_HH

#include <network/packet/PacketSelectPlayer.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketSelectPlayerListener: public PacketListener {
        protected:
            PacketSelectPlayerListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketSelectPlayer *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETSELECTPLAYERLISTENER_HH
