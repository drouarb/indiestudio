//
// Created by drouar_b on 5/12/16.
//

#ifndef CPP_INDIE_STUDIO_PACKETDISCONNECT_HH
#define CPP_INDIE_STUDIO_PACKETDISCONNECT_HH

#include <string>
#include "Packet.hh"

namespace gauntlet {
    namespace network {
        class PacketDisconnect: public Packet {

			PACK(struct s_packetDisconnectData {
				unsigned char packetId;
				unsigned int stringsize;
				char stringstart;
			});

        public:
            PacketDisconnect(const std::string &message, int fd = -1);
            PacketDisconnect(const s_socketData &data);
            virtual ~PacketDisconnect() { }

            virtual t_rawdata* serialize() const;
            virtual void deserialize(t_rawdata* data);
            virtual size_t getPacketSize() const;

            const std::string & getMessage() const;

        private:
            std::string message;
        };
    }
}

#endif //CPP_INDIE_STUDIO_PACKETDISCONNECT_HH
