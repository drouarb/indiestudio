//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETDELETEPARTICLE_HH
#define GAUNTLET_PACKETDELETEPARTICLE_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketDeleteParticle: public Packet {

            struct s_packetDeleteParticle {
                unsigned char packetId;
                unsigned int particleId;
            };

        public:
            PacketDeleteParticle(s_socketData data);
            PacketDeleteParticle(unsigned int particleId);
            virtual ~PacketDeleteParticle() { }

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);
            virtual size_t getPacketSize() const;

            unsigned int getParticleId() const;

        private:
            unsigned int particleId;
        };
    }
}

#endif //GAUNTLET_PACKETDELETEPARTICLE_HH
