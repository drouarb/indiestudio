#include "ListenerStartGame.hh"
#include "WaitPacket.hh"

gauntlet::core::ListenerStartGame::ListenerStartGame(Core & core) : core(core)
{ }

gauntlet::core::ListenerStartGame::~ListenerStartGame()
{ }

void
gauntlet::core::ListenerStartGame::notify(const network::PacketStartGame * packet)
{
  std::cout << "# startgame " << packet->getEntityId() << std::endl;
  WaitPacket::receive(new network::PacketStartGame(packet->getEntityId()));
}
