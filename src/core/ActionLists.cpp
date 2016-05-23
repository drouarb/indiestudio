#include "ActionLists.hh"

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
      core.ogre.addWorldEntity((*it)->getEntityId(), (*it)->getMeshId(),
			       (*it)->getX(), (*it)->getY(), (*it)->getAngle(),
			       (*it)->getTextureId());
    }

  for (std::list<network::PacketAddEntity*>::iterator it = packetsDisconnect.begin();
       it != packetsDisconnect.end(); ++it)
    {
      //TODO: disconnect
      (void)it;
    }

  clearActions();
}

void
gauntlet::core::ActionLists::pushAddEntity(network::PacketAddEntity * packet)
{
  packetsAddEntity.push_back(new network::PacketAddEntity
			     ((*it)->getEntityId(), (*it)->getTextureId(),
			      (*it)->getMeshId(), (*it)->getX(), (*it)->getY(),
			      (*it)->getAngle()));
}

void
gauntlet::core::ActionLists::pushDisconnect(network::PacketDisconnect * packet)
{
  packetsAddEntity.push_back(new network::PacketDisconnect((*it)->getMessage()));
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

  for (std::list<network::PacketAddEntity*>::iterator it = packetsDisconnect.begin();
       it != packetsDisconnect.end(); ++it)
    {
      delete *it;
    }
  packetsDisconnect.clear();
}
