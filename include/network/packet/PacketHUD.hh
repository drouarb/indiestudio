//
// Created by drouar_b on 5/31/16.
//

#ifndef GAUNTLET_PACKETHUD_HH
#define GAUNTLET_PACKETHUD_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketHUD: public Packet {

            PACK(struct s_packetHUDData {
                unsigned char packetId;
                unsigned char health;
            });

        public:
            PacketHUD(s_socketData data);
            PacketHUD(unsigned char health);
            virtual ~PacketHUD() { };

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            unsigned char getHealth() const;

        private:
            unsigned char health;
        };
    }
}

#endif //GAUNTLET_PACKETHUD_HH
