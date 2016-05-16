//
// Created by drouar_b on 5/16/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETSELECTPLAYER_HH
#define CPP_INDIE_STUDIO_PACKETSELECTPLAYER_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketSelectPlayer : public Packet {

            struct s_packetSelectPlayerData {
                unsigned char packetId;
                unsigned char selectedCharacters;
            } __attribute__((packed));

        public:
            PacketSelectPlayer(t_rawdata *data);
            PacketSelectPlayer(bool warrior, bool wizard, bool valkyrie, bool elf);
            virtual ~PacketSelectPlayer() { }

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);

            bool isWarrior() const;
            bool isWizard() const;
            bool isValkyrie() const;
            bool isElf() const;

        private:
            bool warrior;
            bool wizard;
            bool valkyrie;
            bool elf;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETSELECTPLAYER_HH
