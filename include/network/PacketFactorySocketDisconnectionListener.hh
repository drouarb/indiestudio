//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_PACKETFACTORYSOCKETDISCONNECTIONLISTENER_HH
#define GAUNTLET_PACKETFACTORYSOCKETDISCONNECTIONLISTENER_HH


#include "ISocketDisconnectionListener.hh"
#include "PacketFactory.hh"

namespace gauntlet {
    namespace network {
        class PacketFactorySocketDisconnectionListener: public ISocketDisconnectionListener {
        public:
            PacketFactorySocketDisconnectionListener(PacketFactory *);
            virtual void notify(int fd);

        private:
            PacketFactory *factory;
        };
    }
}

#endif //GAUNTLET_PACKETFACTORYSOCKETDISCONNECTIONLISTENER_HH
