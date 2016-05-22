//
// Created by greg on 22/05/16.
//

#include "graph/Effect.hh"

gauntlet::Effect::Effect(OgreUI *ogreUI, gauntlet::EffectType type, int percent)
{
  try
    {
      const std::string &mapped_type = this->_effectName[type];
      this->name = &mapped_type;
    }catch (...)
    {
      throw std::logic_error("Unrecognized type");
    }
  this->_particleSystem = ogreUI->getSceneManager()->createParticleSystem("");
}

Ogre::ParticleSystem *gauntlet::Effect::getParticleSystem()
{
  return this->_particleSystem;
}

std::string const & gauntlet::Effect::getName()
{
  return *this->name;
}


gauntlet::Effect::~Effect()
{
  OGRE_DELETE this->_particleSystem;
}


std::ostream &::gauntlet::operator<<(std::ostream &ostream, const gauntlet::Effect &spell)
{

  return ostream;
}

