//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETADDPARTICLE_HH
#define GAUNTLET_PACKETADDPARTICLE_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketAddParticle : public Packet {

            struct s_packetAddParticle {
                unsigned char packetId;
                unsigned int particleId;
                unsigned int refId;
                double x;
                double y;
                short angle;
                int decayTime;
            }__attribute__((packed));

        public:
            PacketAddParticle(s_socketData data);
            PacketAddParticle(unsigned int particleId, unsigned int refId, double x, double y, short angle,
                              int decayTime);
            virtual ~PacketAddParticle() { }

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            unsigned int getParticleId() const;
            unsigned int getRefId() const;
            double getX() const;
            double getY() const;
            short getAngle() const;
            int getDecayTime() const;

        private:
            unsigned int particleId;
            unsigned int refId;
            double x;
            double y;
            short angle;
            int decayTime;
        };
    }
}

#endif //GAUNTLET_PACKETADDPARTICLE_HH
