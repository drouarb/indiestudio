#include "ActionLists.hh"
#include "Core.hh"

gauntlet::core::ActionLists::ActionLists(Core & core) : core(core)
{ }

gauntlet::core::ActionLists::~ActionLists()
{
  clearActions();
}

void
gauntlet::core::ActionLists::doActions()
{
  for (std::list<network::PacketAddEntity*>::iterator it = packetsAddEntity.begin();
       it != packetsAddEntity.end(); ++it)
    {
      core.ogre.addWorldEntity((*it)->getEntityId(), (EntityName)(*it)->getMeshId(),
			       (*it)->getX(), (*it)->getY(), (*it)->getAngle(),
			       static_cast<gauntlet::TextureName>
			       ((*it)->getTextureId()));
    }

  for (std::list<network::PacketDisconnect*>::iterator it = packetsDisconnect.begin();
       it != packetsDisconnect.end(); ++it)
    {
      //TODO: disconnect
      (void)it;
    }

  for (std::list<network::PacketMoveEntity*>::iterator it = packetsMoveEntity.begin();
       it != packetsMoveEntity.end(); ++it)
    {
      core.ogre.addWorldEntity((*it)->getEntityId(), (EntityName)0,
			       (*it)->getX(), (*it)->getY(), (*it)->getAngle(), gauntlet::TextureName::TEXTURE_NONE);
    }

  clearActions();
}

void
gauntlet::core::ActionLists::pushAddEntity(const network::PacketAddEntity * packet)
{
  packetsAddEntity.push_back(new network::PacketAddEntity
			     (packet->getEntityId(), packet->getTextureId(),
			      packet->getMeshId(), packet->getX(), packet->getY(),
			      packet->getAngle()));
}

void
gauntlet::core::ActionLists::pushDisconnect(const network::PacketDisconnect * packet)
{
  packetsDisconnect.push_back(new network::PacketDisconnect(packet->getMessage()));
}

void
gauntlet::core::ActionLists::pushMoveEntity(const network::PacketMoveEntity * packet)
{
  packetsMoveEntity.push_back(new network::PacketMoveEntity
			      (packet->getEntityId(),
			       packet->getX(), packet->getY(),
			       packet->getAngle()));
}

void
gauntlet::core::ActionLists::clearActions()
{
  for (std::list<network::PacketAddEntity*>::iterator it = packetsAddEntity.begin();
       it != packetsAddEntity.end(); ++it)
    {
      delete *it;
    }
  packetsAddEntity.clear();

  for (std::list<network::PacketDisconnect*>::iterator it = packetsDisconnect.begin();
       it != packetsDisconnect.end(); ++it)
    {
      delete *it;
    }
  packetsDisconnect.clear();

  for (std::list<network::PacketMoveEntity*>::iterator it = packetsMoveEntity.begin();
       it != packetsMoveEntity.end(); ++it)
    {
      delete *it;
    }
  packetsMoveEntity.clear();
}
