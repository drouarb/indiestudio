//
// Created by drouar_b on 5/22/16.
//

#ifndef GAUNTLET_ISOCKETDISCONNECTIONLISTENER_HH
#define GAUNTLET_ISOCKETDISCONNECTIONLISTENER_HH


namespace gauntlet {
    namespace network {
        class ISocketDisconnectionListener {
        public:
            virtual ~ISocketDisconnectionListener() { }
            virtual void notify(int fd) = 0;
        };
    }
}

#endif //GAUNTLET_ISOCKETDISCONNECTIONLISTENER_HH
