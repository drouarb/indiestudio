//
// Created by drouar_b on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETCONNECT_HH
#define CPP_INDIE_STUDIO_PACKETCONNECT_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketConnect : public Packet {

            struct s_packetConnectData {
                unsigned char packetId;
                unsigned int protocolVersion;
            };

        public:
            PacketConnect();
            PacketConnect(t_rawdata* data);

            virtual ~PacketConnect() { };

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);

            unsigned int getProtocolVersion() const;

        private:
            unsigned int protocolVersion;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETCONNECT_HH
