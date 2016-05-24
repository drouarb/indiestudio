//
// Created by drouar_b on 5/16/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETMAP_HH
#define CPP_INDIE_STUDIO_PACKETMAP_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketMap: public Packet {

            struct s_packetMapData {
                unsigned char packetId;
                unsigned int mapId;
            } __attribute__((packed));

        public:
            PacketMap(const s_socketData &data);
            PacketMap(unsigned int mapId);
            virtual ~PacketMap() { };

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            unsigned int getMapId() const;

        private:
            unsigned int mapId;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETMAP_HH
