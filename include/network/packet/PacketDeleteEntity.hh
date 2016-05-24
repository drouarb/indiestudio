//
// Created by drouar_b on 5/24/16.
//

#ifndef GAUNTLET_PACKETDELETEENTITY_HH
#define GAUNTLET_PACKETDELETEENTITY_HH


#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketDeleteEntity: public Packet {

            struct s_packetDeleteEntityData {
                unsigned char packetId;
                unsigned int entityId;
            };

        public:
            PacketDeleteEntity(unsigned int entityId);
            PacketDeleteEntity(const s_socketData &data);
            virtual ~PacketDeleteEntity() { }

            virtual t_rawdata *serialize() const;
            virtual void deserialize(t_rawdata *data);
            virtual size_t getPacketSize() const;

            unsigned int getEntityId() const;

        private:
            unsigned int entityId;
        };
    }
}

#endif //GAUNTLET_PACKETDELETEENTITY_HH
