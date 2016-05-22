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
                unsigned int assetId;
                unsigned int entityId;
                unsigned long namelen;
                char namestart;
            };
        public:
            PacketAddEntity(const s_socketData &data);
            PacketAddEntity(unsigned int assetId, unsigned int entityId, const std::string &playerName);
            virtual ~PacketAddEntity() { };

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);

            unsigned int getAssetId() const;
            unsigned int getEntityId() const;
            const std::string & getPlayerName() const;

        private:
            unsigned int assetId;
            unsigned int entityId;
            std::string playerName;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETADDPLAYER_HH
