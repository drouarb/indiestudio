#include "WaitPacket.hh"
#include "Core.hh"

gauntlet::core::WaitPacket::WaitPacket(Core &core, int idStart, Menu *parent) :
        Menu(core, idStart, parent)
{
    mustClose(true, false);
    packet(NULL, true);
    buttons.push_back(Control(LABEL, "Waiting for server...", NULL, PCENTER,
                              idStart + buttons.size(), core.ogre));
}

gauntlet::core::WaitPacket::~WaitPacket()
{ }

void
gauntlet::core::WaitPacket::draw()
{
    drawButtons();
    sw.set();
    //timer();
}

void
gauntlet::core::WaitPacket::undraw()
{
    sw.set();
    undrawButtons();
}

bool
gauntlet::core::WaitPacket::keyDown(Command c)
{
    if (!getOpen())
        return (false);

    (void) c;
    return (true);
}

bool
gauntlet::core::WaitPacket::receivedValue()
{
    return (receivedSomething(false, false));
}

void
gauntlet::core::WaitPacket::doButton(int btnId, struct t_hitItem &item)
{
    (void) btnId;
    (void) item;
}

void
gauntlet::core::WaitPacket::receive(network::Packet const *rp)
{
    packet(rp, true);
    mustClose(true, true);
}

gauntlet::network::Packet const *
gauntlet::core::WaitPacket::getReceived()
{
    network::Packet const *p = packet(NULL, false);
    packet(NULL, true);
    receivedSomething(true, false);
    return (p);
}

gauntlet::network::Packet const *
gauntlet::core::WaitPacket::packet(network::Packet const *newpacket, bool set)
{
    static network::Packet const *p = NULL;

    if (set)
        p = newpacket;
    return (p);
}

bool
gauntlet::core::WaitPacket::mustClose(bool set, bool val)
{
    static bool mc = false;

    if (set)
        mc = val;
    return (mc);
}

bool
gauntlet::core::WaitPacket::receivedSomething(bool set, bool val)
{
    static bool rcvd = false;

    if (set)
        rcvd = val;
    return (rcvd);
}

void gauntlet::core::WaitPacket::tick()
{
    if (!(mustClose(false, false) == false && sw.ellapsedMs() < 10000))
        {
            mustClose(true, false);
            receivedSomething(true, true);
            setOpen(false);
        }
}


