//
// Created by drouar_b on 5/12/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETHANDSHAKE_HH
#define CPP_INDIE_STUDIO_PACKETHANDSHAKE_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketHandshake : public Packet {

            struct s_packetHandshakeData {
                unsigned char packetId;
                unsigned char maxPlayers;
                unsigned char connectedPlayers;
                unsigned char avaibleCharacters;
            };

        public:
            PacketHandshake();
            PacketHandshake(t_rawdata *data);

            virtual ~PacketHandshake() { };

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);

            bool isWarrior() const;
            bool isWizard() const;
            bool isValkyrie() const;
            bool isElf() const;
            unsigned char getMaxPlayers() const;
            unsigned char getConnectedPlayers() const;

        private:
            bool warrior;
            bool wizard;
            bool valkyrie;
            bool elf;
            unsigned char maxPlayers;
            unsigned char connectedPlayers;
        };
    }
}


#endif //CPP_INDIE_STUDIO_PACKETHANDSHAKE_HH
