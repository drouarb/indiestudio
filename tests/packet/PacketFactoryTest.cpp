//
// Created by drouar_b on 5/22/16.
//

#include <unistd.h>
#include <iostream>
#include <thread>
#include <assert.h>
#include <network/listener/PacketAddEntityListener.hh>
#include "network/listener/PacketDisconnectListener.hh"
#include "network/PacketFactory.hh"

class PacketDisconnectListenerTest: public gauntlet::network::PacketDisconnectListener {
public:
    PacketDisconnectListenerTest(): count(0) {};

    virtual void notify(const gauntlet::network::PacketDisconnect *packet) {
        std::cout << "    -> " << packet->getSocketId() << " disconnected" << std::endl;
        count++;
    }

    int getCount() {
        return count;
    }

private:
    int count;
};

class PacketAddEntityListenerTest: public gauntlet::network::PacketAddEntityListener {
public:
    PacketAddEntityListenerTest(): count(0) {};

    virtual void notify(const gauntlet::network::PacketAddEntity *packet) {
        std::cout << "    ->  Entity received" << std::endl;
        mut.lock();
        count++;
        mut.unlock();
    }

    int getCount() {
        return count;
    }

private:
    int count;
    std::mutex mut;
};

void server_func(gauntlet::network::PacketFactory *server) {
    server->recv();
}

void cli1_func(gauntlet::network::PacketFactory *cli1) {
    cli1->recv();
}

void cli2_func(gauntlet::network::PacketFactory *cli2) {
    cli2->recv();
}

int main() {
    std::cout << "Testing PacketFactory" << std::endl;
    std::cout << "  -- Instantiating server & clients" << std::endl;
    srand(time(NULL));
    gauntlet::network::PacketFactory *server = new gauntlet::network::PacketFactory(54918);
    std::thread *serverThread = new std::thread(&server_func, server);
    gauntlet::network::PacketFactory *cli1 = new gauntlet::network::PacketFactory("127.0.0.1", 54918);
    std::thread *cli1Thread = new std::thread(&cli1_func, cli1);
    gauntlet::network::PacketFactory *cli2 = new gauntlet::network::PacketFactory("127.0.0.1", 54918);
    std::thread *cli2Thread = new std::thread(&cli2_func, cli2);
    sleep(1);
    std::cout << "  -> OK" << std::endl;

    std::cout << "  -- Registering listeners" << std::endl;
    PacketDisconnectListenerTest *packetDisconnectTest = new PacketDisconnectListenerTest;
    PacketAddEntityListenerTest *packetAddEntityListenerTest = new PacketAddEntityListenerTest;
    server->registerListener(packetDisconnectTest);
    cli1->registerListener(packetAddEntityListenerTest);
    cli2->registerListener(packetAddEntityListenerTest);
    std::cout << "  -> OK" << std::endl;

    std::cout << "  -- Sending some packets" << std::endl;
    gauntlet::network::PacketAddEntity *packetAddEntity = new gauntlet::network::PacketAddEntity(rand(), rand(), "Hi bro");
    server->send(*packetAddEntity);
    sleep(1);
    std::cout << "  -- OK" << std::endl;

    std::cout << "  -- Stopping server & clients" << std::endl;
    cli1->stop();
    cli1Thread->join();
    delete(cli1Thread);
    delete(cli1);
    cli2->stop();
    cli2Thread->join();
    delete(cli2Thread);
    delete(cli2);
    sleep(1);
    assert(packetDisconnectTest->getCount() == 2);
    server->stop();
    serverThread->join();
    delete(serverThread);
    delete(server);;
    std::cout << "  -> OK" << std::endl;
}