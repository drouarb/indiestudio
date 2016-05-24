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
            } __attribute__((packed));

        public:
            PacketHandshake(const s_socketData &data);
            PacketHandshake(bool warrior, bool wizard, bool valkyrie, bool elf, unsigned char maxPlayers,
                            unsigned char connectedPlayers);

            virtual ~PacketHandshake() { };

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            bool getWarrior() const;
            bool getWizard() const;
            bool getValkyrie() const;
            bool getElf() const;
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
