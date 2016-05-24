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
                unsigned int namelen;
                char namestart;
            } __attribute__((packed));

        public:
            PacketSelectPlayer(const s_socketData &data);
            PacketSelectPlayer(bool warrior, bool wizard, bool valkyrie, bool elf, const std::string &name);
            virtual ~PacketSelectPlayer() { }

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            bool getWarrior() const;
            bool getWizard() const;
            bool getValkyrie() const;
            bool getElf() const;
            const std::string & getName() const;

        private:
            bool warrior;
            bool wizard;
            bool valkyrie;
            bool elf;
            std::string name;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETSELECTPLAYER_HH
