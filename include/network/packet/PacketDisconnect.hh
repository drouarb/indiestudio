//
// Created by drouar_b on 5/12/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETDISCONNECT_HH
#define CPP_INDIE_STUDIO_PACKETDISCONNECT_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketDisconnect: public Packet {

            struct s_packetDisconnectData {
                unsigned char packetId;
                unsigned long stringsize;
                char stringstart;
            };

        public:
            PacketDisconnect();
            PacketDisconnect(t_rawdata *data);
            ~PacketDisconnect() { }

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);

            const std::string & getMessage() const;

        private:
            std::string message;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETDISCONNECT_HH
