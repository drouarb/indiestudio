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
                unsigned char loop;
            };

        public:
            PacketPlaySound(s_socketData data);
            PacketPlaySound(unsigned int soundId, unsigned int refId, bool loop);
            virtual ~PacketPlaySound() { }

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);
            virtual size_t getPacketSize() const;

            unsigned int getSoundId() const;
            unsigned int getRefId() const;
            bool getLoop() const;

        private:
            unsigned int soundId;
            unsigned int refId;
            bool loop;
        };
    }
}


#endif //GAUNTLET_PACKETPLAYSOUND_HH
