//
// Created by drouar_b on 06/05/16.
//

#ifndef CPP_INDIE_STUDIO_PACKET_HPP
#define CPP_INDIE_STUDIO_PACKET_HPP

#include <stdlib.h>
#include <vector>
#include "network/Socket.hh"

#ifdef _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#define PROTOCOL_VERSION    1

typedef std::vector<unsigned char> t_rawdata;
namespace gauntlet {
    namespace network {

        enum PacketId: unsigned char {
            CONNECT               = 0x01,
            DISCONNECT            = 0x02,
            HANDSHAKE             = 0x03,
            PLAYER_SELECT         = 0x04,
            START_GAME            = 0x05,
            MAP                   = 0x06,
            ADD_ENTITY            = 0x07,
            MOVE_ENTITY           = 0x08,
            DELETE_ENTITY         = 0x09,
            ADD_PARTICLE          = 0x0A,
            DELETE_PARTICLE       = 0x0B,
            PLAY_SOUND            = 0x0C,
            STOP_SOUND            = 0x0D,
            PACKET_CONTROL        = 0x0E,
            ANIMATION             = 0x0F,
            HUD                   = 0x10
        };

        class Packet {
        protected:
            Packet(PacketId packetId, int socketId);

        public:
            virtual ~Packet() {};
            PacketId getPacketId() const;
            int getSocketId() const;

            virtual t_rawdata* serialize() const = 0;
            virtual void deserialize(t_rawdata* data) = 0;
            virtual size_t getPacketSize() const = 0;

        private:
            const PacketId packetId;
            const int socketId;
        };
    }
}


#endif //CPP_INDIE_STUDIO_PACKET_HPP
