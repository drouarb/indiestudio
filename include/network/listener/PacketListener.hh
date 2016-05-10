//
// Created by drouar_b on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_IPACKETLISTENER_HH
#define CPP_INDIE_STUDIO_IPACKETLISTENER_HH

#include "network/packet/Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketListener {
        protected:
            PacketListener(PacketId id);

        public:
            PacketId getPacketId() const;

            virtual void notify(Packet *) = 0;

        private:
            PacketId packetId;
        };
    }
}
#endif //CPP_INDIE_STUDIO_IPACKETLISTENER_HH
