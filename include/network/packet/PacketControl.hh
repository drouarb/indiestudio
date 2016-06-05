//
// Created by drouar_b on 5/25/16.
//

#ifndef GAUNTLET_PACKETCONTROL_HH
#define GAUNTLET_PACKETCONTROL_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketControl: public Packet {

            PACK(struct s_packetControlData {
                unsigned char packetId;
                unsigned char cmd;
                short angle;
            });

        public:
            PacketControl(s_socketData data);
            PacketControl(unsigned char cmd, short angle);
            virtual ~PacketControl() { }

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);
            virtual size_t getPacketSize() const;

            unsigned char getCmd() const;
            short getAngle() const;

        private:
            unsigned char cmd;
            short angle;
        };
    }
}

#endif //GAUNTLET_PACKETCONTROL_HH
