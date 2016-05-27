//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETMOVEENTITY_HH
#define GAUNTLET_PACKETMOVEENTITY_HH

#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketMoveEntity: public Packet {

            struct s_packetMoveEntityData {
                unsigned char packetId;
                unsigned int entityId;
                double x;
                double y;
                short angle;
            }__attribute__((packed));

        public:
            PacketMoveEntity(s_socketData data);
            PacketMoveEntity(unsigned int entityId, double x, double y, short angle);
            virtual ~PacketMoveEntity() { };

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);

            unsigned int getEntityId() const;
            double getX() const;
            double getY() const;
            short getAngle() const;
            virtual size_t getPacketSize() const;

        private:
            unsigned int entityId;
            double x;
            double y;
            short angle;
        };
    }
}

#endif //GAUNTLET_PACKETMOVEENTITY_HH
