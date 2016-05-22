//
// Created by drouar_b on 5/21/16.
//

#include <string.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include "network/Socket.hh"

#define KEY_PHRASE "Tanguy l'enlise nous a encore envoyé dans un guet-apens."

void socket_server(gauntlet::network::Socket *s, std::vector<s_socketData>* cbuffs)
{
    cbuffs->push_back(s->recv());
    cbuffs->push_back(s->recv());
}

int main() {
    std::cout << "Testing Socket" << std::endl;

    std::cout << "  -- Instantiating server & clients" << std::endl;
    gauntlet::network::Socket *ss = new gauntlet::network::Socket(54917);
    std::vector<s_socketData> cbuffs;
    std::thread *t = new std::thread(&socket_server, ss, &cbuffs);
    gauntlet::network::Socket *sc1 = new gauntlet::network::Socket("127.0.0.1", 54917);
    sleep(1);
    gauntlet::network::Socket *sc2 = new gauntlet::network::Socket("127.0.0.1", 54917);
    sleep(1);
    std::cout << "  -> OK" << std::endl;

    std::vector<unsigned char> *servbuff = new std::vector<unsigned char>();
    servbuff->resize(60, 0);
    strcpy((char *)&servbuff->front(), KEY_PHRASE);

    std::cout << "  -- Sending data from server to clients" << std::endl;
    ss->send(servbuff);
    std::cout << "  -> OK" << std::endl;

    std::cout << "  -- Receiving data from server to client" << std::endl;
    s_socketData cli1buff = sc1->recv();
    s_socketData cli2buff = sc2->recv();

    assert(servbuff->size() == cli1buff.data->size());
    assert(servbuff->size() == cli2buff.data->size());
    assert(strcmp(KEY_PHRASE, (char *)&cli1buff.data->front()) == 0);
    assert(strcmp(KEY_PHRASE, (char *)&cli2buff.data->front()) == 0);
    std::cout << "  -> OK" << std::endl;

    std::cout << "  -- Sending data from clients to server" << std::endl;
    cli1buff.data->push_back('1');
    cli2buff.data->push_back('2');
    sc1->send(cli1buff.data);
    sc2->send(cli2buff.data);
    sleep(1);
    std::cout << "  -> OK" << std::endl;
    assert(cbuffs[0].data->back() == '1' || cbuffs[0].data->back() == '2');
    assert(cbuffs[1].data->back() == '1' || cbuffs[1].data->back() == '2');

    delete(sc1);
    delete(sc2);
    delete(ss);
}