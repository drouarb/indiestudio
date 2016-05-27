//
// Created by drouar_b on 5/27/16.
//

#ifndef GAUNTLET_PACKETANIMATION_HH
#define GAUNTLET_PACKETANIMATION_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketAnimation: public Packet {

            struct s_packetAnimationData {
                unsigned char packetId;
                unsigned int entityId;
                unsigned int animationId;
            };

        public:
            PacketAnimation(s_socketData data);
            PacketAnimation(unsigned int entityId, unsigned int animationId);
            virtual ~PacketAnimation() { }

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            unsigned int getEntityId() const;
            unsigned int getAnimationId() const;

        private:
            unsigned int entityId;
            unsigned int animationId;
        };
    }
}

#endif //GAUNTLET_PACKETANIMATION_HH
