//
// Created by drouar_b on 5/16/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETMAP_HH
#define CPP_INDIE_STUDIO_PACKETMAP_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketMap: public Packet {

            PACK(struct s_packetMapData {
                unsigned char packetId;
                unsigned int mapId;
                unsigned int stringsize;
                char stringstart;

            });

        public:
            PacketMap(const s_socketData &data);
            PacketMap(unsigned int mapId, const std::string &filename);
            virtual ~PacketMap() { };

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            unsigned int getMapId() const;
            const std::string & getFilename() const;

        private:
            unsigned int mapId;
            std::string filename;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETMAP_HH
