//
// Created by drouar_b on 5/24/16.
//

#ifndef GAUNTLET_PACKETSTARTGAME_HH
#define GAUNTLET_PACKETSTARTGAME_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketStartGame: public Packet {

            struct s_packetStartGameData {
                unsigned char packetId;
                unsigned int entityId;
            };

        public:
            PacketStartGame(unsigned int entityId);
            PacketStartGame(const s_socketData &data);
            virtual ~PacketStartGame() { }

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);

            unsigned int getEntityId() const;

        private:
            unsigned int entityId;
        };
    }
}

#endif //GAUNTLET_PACKETSTARTGAME_HH
