#include "ActionLists.hh"
#include "Core.hh"
#include "EffectName.hh"

gauntlet::core::ActionLists::ActionLists(Core & core) : core(core), pendingTracker(false)
{ }

gauntlet::core::ActionLists::~ActionLists()
{
  clearActions();
}

void
gauntlet::core::ActionLists::doActions()
{
  if (packetsDisconnect.size() > 0 && core.gameIsRunning())
    {
      core.disconnect();
    }
  else
    {
      for (std::list<network::PacketAddEntity*>::iterator it = packetsAddEntity.begin();
	   it != packetsAddEntity.end(); ++it)
	{
	  core.ogre.addWorldEntity((*it)->getEntityId(), (EntityName)(*it)->getMeshId(),
				   (*it)->getX(), (*it)->getY(), (*it)->getAngle(),
				   static_cast<gauntlet::TextureName>
				   ((*it)->getTextureId()));
	  core.ogre.playAnimation((*it)->getEntityId(), 0, true);

	  if (pendingTracker && (*it)->getEntityId() == entityIdTracker)
	    {
	      core.ogre.addCameraTracker((*it)->getEntityId());
	      pendingTracker = false;
	    }
	}

      for (std::list<network::PacketMoveEntity*>::iterator it = packetsMoveEntity.begin();
	   it != packetsMoveEntity.end(); ++it)
	{
	  core.ogre.addWorldEntity((*it)->getEntityId(), (EntityName)0,
				   (*it)->getX(), (*it)->getY(), (*it)->getAngle(),
				   gauntlet::TextureName::TEXTURE_NONE);
	}

      for (std::list<network::PacketDeleteEntity*>::iterator
	     it = packetsDeleteEntity.begin(); it != packetsDeleteEntity.end(); ++it)
	{
	  core.ogre.removeEntity((*it)->getEntityId());
	}

      for (std::list<network::PacketAddParticle*>::iterator
	     it = packetsAddParticle.begin(); it != packetsAddParticle.end(); ++it)
	{
	  core.ogre.triggerEffect((*it)->getRefId(), (EffectName)(*it)->getParticleId(),
				  std::pair<double, double>
				  ((double)(*it)->getX(), (double)(*it)->getY()));
	}

      for (std::list<network::PacketDeleteParticle*>::iterator
	     it = packetsDeleteParticle.begin(); it != packetsDeleteParticle.end(); ++it)
	{
	  core.ogre.stopEffect((*it)->getParticleId());
	}

      for (std::list<network::PacketPlaySound*>::iterator
	     it = packetsPlaySound.begin(); it != packetsPlaySound.end(); ++it)
	{
	  (void)it;
	  //TODO
	}

      for (std::list<network::PacketStopSound*>::iterator
	     it = packetsStopSound.begin(); it != packetsStopSound.end(); ++it)
	{
	  //core.ogre.stopSound((*it)->getSoundId());
	}
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
  allPackets.push_back(packetsAddEntity.back());
}

void
gauntlet::core::ActionLists::pushDisconnect(const network::PacketDisconnect * packet)
{
  packetsDisconnect.push_back(new network::PacketDisconnect(packet->getMessage()));
  allPackets.push_back(packetsDisconnect.back());
}

void
gauntlet::core::ActionLists::pushMoveEntity(const network::PacketMoveEntity * packet)
{
  packetsMoveEntity.push_back(new network::PacketMoveEntity
			      (packet->getEntityId(),
			       packet->getX(), packet->getY(),
			       packet->getAngle()));
  allPackets.push_back(packetsMoveEntity.back());
}

void
gauntlet::core::ActionLists::pushDeleteEntity(const network::PacketDeleteEntity * packet)
{
  packetsDeleteEntity.push_back(new network::PacketDeleteEntity(packet->getEntityId()));
  allPackets.push_back(packetsDeleteEntity.back());
}

void
gauntlet::core::ActionLists::pushStopSound(const network::PacketStopSound * packet)
{
  packetsStopSound.push_back(new network::PacketStopSound(packet->getSoundId()));
  allPackets.push_back(packetsStopSound.back());
}

void
gauntlet::core::ActionLists::pushPlaySound(const network::PacketPlaySound * packet)
{
  packetsPlaySound.push_back(new network::PacketPlaySound(packet->getSoundId(),
							  packet->getRefId(),
							  packet->getLoop()));
  allPackets.push_back(packetsPlaySound.back());
}

void
gauntlet::core::ActionLists::pushAddParticle(const network::PacketAddParticle * packet)
{
  packetsAddParticle.push_back(new network::PacketAddParticle
			       (packet->getParticleId(), packet->getRefId(),
				packet->getX(), packet->getY(),
				packet->getDecayTime()));
  allPackets.push_back(packetsAddParticle.back());
}

void
gauntlet::core::ActionLists::pushDeleteParticle(const network::PacketDeleteParticle * packet)
{
  packetsDeleteParticle.push_back(new network::PacketDeleteParticle
				  (packet->getParticleId()));
  allPackets.push_back(packetsDeleteParticle.back());
}

void
gauntlet::core::ActionLists::clearActions()
{
  for (std::list<network::Packet*>::iterator it = allPackets.begin();
       it != allPackets.end(); ++it)
    {
      delete *it;
    }
  allPackets.clear();

  packetsAddEntity.clear();
  packetsDisconnect.clear();
  packetsMoveEntity.clear();
  packetsDeleteEntity.clear();
  packetsStopSound.clear();
  packetsPlaySound.clear();
  packetsAddParticle.clear();
  packetsDeleteParticle.clear();
}

void gauntlet::core::ActionLists::setCameraTrackerId(int id)
{
  entityIdTracker = id;
  pendingTracker = true;
}
