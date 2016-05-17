//
// Created by drouar_b on 5/16/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETADDPLAYER_HH
#define CPP_INDIE_STUDIO_PACKETADDPLAYER_HH


#include <string>
#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketAddPlayer : public Packet {

            struct s_PacketAddPlayer {
                unsigned char packetId;
                unsigned int assetId;
                unsigned int entityId;
                unsigned long namelen;
                char namestart;
            };
        public:
            PacketAddPlayer(t_rawdata *data);
            PacketAddPlayer(unsigned int packetId, unsigned int entityId, const std::string &playerName);
            virtual ~PacketAddPlayer() { };

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
