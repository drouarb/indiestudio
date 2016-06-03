#include "ActionLists.hh"
#include "Core.hh"
#include "Math.hh"

gauntlet::core::ActionLists::ActionLists(Core &core) : core(core), pendingTracker(false)
{ }

gauntlet::core::ActionLists::~ActionLists()
{
    clearActions();
}

gauntlet::core::ActionLists::particle::particle(int id, int decaytime) :
        id(id), decayTime(decaytime)
{
    sw.set();
}

void
gauntlet::core::ActionLists::particlesDecay()
{
    for (std::list<particle *>::iterator it = particles.begin(); it != particles.end(); ++it)
        {
            if ((*it)->sw.ellapsedMs() >= (*it)->decayTime)
                {
                    packetsDeleteParticle.push_back(new network::PacketDeleteParticle((*it)->id));
                    allPackets.push_back(packetsDeleteParticle.back());
                    delete (*it);
                    it = particles.erase(it);
                    it--;
                }
        }
}

void
gauntlet::core::ActionLists::doActions()
{
    mutex.lock();
    if (packetsDisconnect.size() > 0 && core.gameIsRunning())
        {
            bool done = false;
            for (std::list<network::PacketDisconnect *>::iterator it = packetsDisconnect.begin();
                    it != packetsDisconnect.end(); ++it)
                {
                    if ((*it)->getMessage() != "")
                        {
                            done = true;
                            core.disconnect((*it)->getMessage());
                            break ;
                        }
                }
            if (!done)
                {
                    core.disconnect(packetsDisconnect.front()->getMessage());
                }
        }
    else
        {
            particlesDecay();

            for (std::list<network::PacketMap *>::iterator
                         it = packetsMap.begin(); it != packetsMap.end(); ++it)
                {
                    if ((*it) == NULL)
                        {
                            continue;
                        }
                    std::size_t index = (*it)->getFilename().find(';');
                    if (index != std::string::npos)
                        {
                            std::cerr << (*it)->getFilename() << std::endl;
                            core.ogre.loadMap((*it)->getFilename().substr(index + 1));
                            core.ogre.addMapEntity(-1, (*it)->getFilename().substr(0, index),
                                                   0, 0, 0, TEXTURE_NONE);
                        }
                }

            for (std::list<network::PacketAddEntity *>::iterator it = packetsAddEntity.begin();
                 it != packetsAddEntity.end(); ++it)
                {
                    core.ogre.addWorldEntity((*it)->getEntityId(), (EntityName) (*it)->getMeshId(),
                                             (*it)->getX(), (*it)->getY(),
                                             (*it)->getAngle() - world::Math::A_RIGHT,
                                             static_cast<gauntlet::TextureName>
                                             ((*it)->getTextureId()));

                    if (pendingTracker && (*it)->getEntityId() == entityIdTracker)
                        {
                            core.ogre.addCameraTracker((*it)->getEntityId());
                            pendingTracker = false;
                        }
                }

            for (std::list<network::PacketMoveEntity *>::iterator it = packetsMoveEntity.begin();
                 it != packetsMoveEntity.end(); ++it)
                {
                    if (core.ogre.entityExist((*it)->getEntityId()))
                        core.ogre.addWorldEntity((*it)->getEntityId(), (EntityName) 0,
                                                 (*it)->getX(), (*it)->getY(),
                                                 (*it)->getAngle() - world::Math::A_RIGHT,
                                                 gauntlet::TextureName::TEXTURE_NONE);
                }

            for (std::list<network::PacketDeleteEntity *>::iterator
                         it = packetsDeleteEntity.begin(); it != packetsDeleteEntity.end(); ++it)
                {
                    core.ogre.removeEntity((*it)->getEntityId());
                }

            for (std::list<network::PacketAddParticle *>::iterator
                         it = packetsAddParticle.begin(); it != packetsAddParticle.end(); ++it)
                {
                    core.ogre.triggerEffect((*it)->getRefId(), (EffectName) (*it)->getParticleId(),
                                            std::pair<double, double>
                                                    ((*it)->getX(), (*it)->getY()));
                }

            for (std::list<network::PacketDeleteParticle *>::iterator
                         it = packetsDeleteParticle.begin(); it != packetsDeleteParticle.end(); ++it)
                {
                    try
                        {
                            core.ogre.stopEffect((*it)->getParticleId());
                        }
                    catch (...)
                        { }
                }

            for (std::list<network::PacketPlaySound *>::iterator
                         it = packetsPlaySound.begin(); it != packetsPlaySound.end(); ++it)
                {
                    if ((*it)->getX() < 0 || (*it)->getY() < 0)
                        core.ogre.playSound((*it)->getRefId() + 1, (SoundName) (*it)->getSoundId(),
                                            (*it)->getLoop());
                    else
                        core.ogre.play3dSound((*it)->getRefId() + 1, (SoundName) (*it)->getSoundId(), (*it)->getX(),
                                              (*it)->getY(), false);
                    //TODO else: localized sound
                }

            for (std::list<network::PacketStopSound *>::iterator
                         it = packetsStopSound.begin(); it != packetsStopSound.end(); ++it)
                {
                    core.ogre.stopSound((*it)->getSoundId() + 1);
                }

            for (std::list<network::PacketAnimation *>::iterator
                         it = packetsAnimation.begin(); it != packetsAnimation.end(); ++it)
                {
                    if (core.ogre.entityExist((*it)->getEntityId()))
                        core.ogre.playAnimation((*it)->getEntityId(),
                                                static_cast<animations::AnimationsListJson>((*it)->getAnimationId()),
                                                (*it)->isLoop());
                }

            if (packetsHUD.size() > 0)
                {
                    core.hud.setStats(packetsHUD.back()->getHealth());
                }
        }
    clearActions();
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushAddEntity(const network::PacketAddEntity *packet)
{
    mutex.lock();
    packetsAddEntity.push_back(new network::PacketAddEntity
                                       (packet->getEntityId(), packet->getTextureId(),
                                        packet->getMeshId(), packet->getX(), packet->getY(),
                                        packet->getAngle()));
    allPackets.push_back(packetsAddEntity.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushDisconnect(const network::PacketDisconnect *packet)
{
    mutex.lock();
    packetsDisconnect.push_back(new network::PacketDisconnect(packet->getMessage()));
    allPackets.push_back(packetsDisconnect.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushMoveEntity(const network::PacketMoveEntity *packet)
{
    mutex.lock();
    packetsMoveEntity.push_back(new network::PacketMoveEntity
                                        (packet->getEntityId(),
                                         packet->getX(), packet->getY(),
                                         packet->getAngle()));
    allPackets.push_back(packetsMoveEntity.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushDeleteEntity(const network::PacketDeleteEntity *packet)
{
    mutex.lock();
    packetsDeleteEntity.push_back(new network::PacketDeleteEntity(packet->getEntityId()));
    allPackets.push_back(packetsDeleteEntity.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushStopSound(const network::PacketStopSound *packet)
{
    mutex.lock();
    packetsStopSound.push_back(new network::PacketStopSound(packet->getSoundId()));
    allPackets.push_back(packetsStopSound.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushPlaySound(const network::PacketPlaySound *packet)
{
    mutex.lock();
    packetsPlaySound.push_back(new network::PacketPlaySound(packet->getSoundId(),
                                                            packet->getRefId(), packet->getX(), packet->getY(),
                                                            packet->getLoop()));
    allPackets.push_back(packetsPlaySound.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushAddParticle(const network::PacketAddParticle *packet)
{
    mutex.lock();
    packetsAddParticle.push_back(new network::PacketAddParticle
                                         (packet->getParticleId(), packet->getRefId(),
                                          packet->getX(), packet->getY(), packet->getAngle(),
                                          packet->getDecayTime()));
    allPackets.push_back(packetsAddParticle.back());
    if (packet->getDecayTime() > 0)
        particles.push_back(new particle(packet->getRefId(), packet->getDecayTime()));
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushDeleteParticle(const network::PacketDeleteParticle *packet)
{
    mutex.lock();
    packetsDeleteParticle.push_back(new network::PacketDeleteParticle
                                            (packet->getParticleId()));
    allPackets.push_back(packetsDeleteParticle.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushAnimation(const network::PacketAnimation *packet)
{
    mutex.lock();
    packetsAnimation.push_back(new network::PacketAnimation
                                       (packet->getEntityId(), packet->getAnimationId(), packet->isLoop()));
    allPackets.push_back(packetsAnimation.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::pushMap(const network::PacketMap *packet)
{
    mutex.lock();
    packetsMap.push_back(new network::PacketMap(packet->getMapId(), packet->getFilename()));
    allPackets.push_back(packetsMap.back());
    mutex.unlock();
}

void gauntlet::core::ActionLists::pushHUD(const network::PacketHUD *packet)
{
    mutex.lock();
    packetsHUD.push_back(new network::PacketHUD(packet->getHealth()));
    allPackets.push_back(packetsHUD.back());
    mutex.unlock();
}

void
gauntlet::core::ActionLists::clearActions()
{
    for (std::list<network::Packet *>::iterator it = allPackets.begin();
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
    packetsAnimation.clear();
    packetsMap.clear();
    packetsHUD.clear();
}

void gauntlet::core::ActionLists::setCameraTrackerId(int id)
{
    entityIdTracker = id;
    pendingTracker = true;
}


