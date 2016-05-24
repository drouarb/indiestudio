//
// Created by drouar_b on 5/16/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETADDPLAYER_HH
#define CPP_INDIE_STUDIO_PACKETADDPLAYER_HH


#include <string>
#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketAddEntity : public Packet {

            struct s_PacketAddEntity {
                unsigned char packetId;
                unsigned int entityId;
                unsigned int textureId;
                unsigned int meshId;
	      int x;
                int y;
                short angle;
            }__attribute__((packed));

        public:
            PacketAddEntity(const s_socketData &data);
            PacketAddEntity(unsigned int entityId, unsigned int textureId, unsigned int meshId, int x, int y, short angle);
            virtual ~PacketAddEntity() { };

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);


            unsigned int getEntityId() const;
            unsigned int getTextureId() const;
            unsigned int getMeshId() const;
            int getX() const;
            int getY() const;
            short getAngle() const;

        private:
            unsigned int entityId;
            unsigned int textureId;
            unsigned int meshId;
            int x;
            int y;
            short angle;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETADDPLAYER_HH
