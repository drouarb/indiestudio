//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETSTOPSOUND_HH
#define GAUNTLET_PACKETSTOPSOUND_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketStopSound: public Packet {

            struct s_packetStopSound {
                unsigned char packetId;
                unsigned int soundId;
            }__attribute__((packed));

        public:
            PacketStopSound(s_socketData data);
            PacketStopSound(unsigned int soundId);
            virtual ~PacketStopSound() { };

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);
            virtual size_t getPacketSize() const;

            unsigned int getSoundId() const;

        private:
            unsigned int soundId;
        };
    }
}

#endif //GAUNTLET_PACKETSTOPSOUND_HH
