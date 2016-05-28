//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETPLAYSOUND_HH
#define GAUNTLET_PACKETPLAYSOUND_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketPlaySound: public Packet {

            struct s_packetPlaySoundData {
                unsigned char packetId;
                unsigned int soundId;
                unsigned int refId;
                double x;
                double y;
                unsigned char loop;
            }__attribute__((packed));

        public:
            PacketPlaySound(s_socketData data);
            PacketPlaySound(unsigned int soundId, unsigned int refId, double x, double y, bool loop);
            virtual ~PacketPlaySound() { }

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);
            virtual size_t getPacketSize() const;

            unsigned int getSoundId() const;
            unsigned int getRefId() const;
            double getX() const;
            double getY() const;
            bool getLoop() const;

        private:
            unsigned int soundId;
            unsigned int refId;
            double x;
            double y;
            bool loop;
        };
    }
}


#endif //GAUNTLET_PACKETPLAYSOUND_HH
