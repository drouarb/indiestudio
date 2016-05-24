//
// Created by drouar_b on 5/24/16.
//

#ifndef GAUNTLET_PACKETDELETEENTITYLISTENER_HH
#define GAUNTLET_PACKETDELETEENTITYLISTENER_HH


#include <network/packet/PacketDeleteEntity.hh>
#include "PacketListener.hh"

namespace gauntlet {
    namespace network {
        class PacketDeleteEntityListener : public PacketListener {
        protected:
            PacketDeleteEntityListener();
        public:
            virtual void notify(const Packet *packet);
            virtual void notify(const PacketDeleteEntity *packet) = 0;
        };
    }
}

#endif //GAUNTLET_PACKETDELETEENTITYLISTENER_HH
