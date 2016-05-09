//
// Created by drouar_b on 06/05/16.
//

#ifndef CPP_INDIE_STUDIO_PACKET_HPP
#define CPP_INDIE_STUDIO_PACKET_HPP

#include <stdlib.h>

#define PROTOCOL_VERSION    1

namespace gauntlet {
    namespace network {
        enum PacketId: unsigned char {
            CONNECT               = 0x01,
            DISCONNECT            = 0x02,
            HANDSHAKE             = 0x03,
            PLAYERSELECT          = 0x04,
            MAP                   = 0x05,
            ADD_PLAYER            = 0x06,
            ADD_CREATURE          = 0x07,
            ADD_GAMEOBJECT        = 0x08,
            MOVE_ENTITY           = 0x09,
            UPDATE_ENTITY         = 0x0A,
            DELETE_ENTITY         = 0x0B,
            ADD_PARTICLE          = 0x0C,
            DELETE_PARTICLE       = 0x0D,
            CREATE_INVENTORY      = 0x0E,
            UPDATE_INVENTORY      = 0x0F,
            DELETE_INVENTORY      = 0x10
        };

        class Packet {
        protected:
            Packet(PacketId packetId);

        public:
            virtual ~Packet() {};
            PacketId getPacketId() const;

            virtual void *serialize(size_t &size) const = 0;
            virtual void deserialize(void *data) = 0;

        private:
            const PacketId packetId;
        };
    }
}


#endif //CPP_INDIE_STUDIO_PACKET_HPP
