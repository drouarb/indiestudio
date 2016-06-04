//
// Created by greg on 22/05/16.
//

#include "graph/Effect.hh"

gauntlet::Effect::Effect(OgreUI *ogreUI, gauntlet::EffectName type, std::string const &name, std::pair<double, double> coord, int percent)
{
  try
    {
      const std::string &mapped_type = this->_effectName[type];
      this->name = &mapped_type;
    }catch (...)
    {
      throw std::logic_error("Unrecognized type");
    }
//  std::cout << "\t--------------------\tName: " << name << "*this->name" << *this->name << std::endl;
  Ogre::SceneManager *pManager = ogreUI->getSceneManager();
  if (!pManager)
    {
      throw std::runtime_error("Cannot find SceneManager");
    }
  try
    {
      this->_particleSystem = pManager->createParticleSystem(name, *this->name);
    }
  catch (std::exception &e)
    {
      this->_particleSystem = pManager->getParticleSystem(name);
    }
  if (this->_particleSystem == NULL)
    {
      throw std::runtime_error("Template " + name + " not found");
    }
  Ogre::SceneNode* particleNode = pManager->getRootSceneNode()->createChildSceneNode(name + "scene");
  const Ogre::Vector3 &scale = particleNode->getScale() / _EFFECT_DIVIDE_SIZE;
  std::cout << "scale effect: " << scale << ", original:" << particleNode->getScale() << std::endl;
  particleNode->setScale(scale);
  particleNode->setPosition((Ogre::Vector3(static_cast<float>(coord.first), ogreUI->getHeightAt(coord.first, coord.second), static_cast<float >(coord.second))));
  for (size_t i = 0; i < _particleSystem->getNumEmitters(); ++i)
    {
      Ogre::ParticleEmitter *pEmitter = _particleSystem->getEmitter(i);
      pEmitter->setDuration(pEmitter->getDuration() / _EFFECT_DIVIDE_SIZE);
    }
  float quota = static_cast<float>(this->_particleSystem->getParticleQuota()) *
		static_cast<float>(percent);
  this->_particleSystem->setParticleQuota(quota / 100.0);
  particleNode->attachObject(this->_particleSystem);
}

Ogre::ParticleSystem *gauntlet::Effect::getParticleSystem() const
{
  return this->_particleSystem;
}

std::string const & gauntlet::Effect::getName() const
{
  return *this->name;
}


gauntlet::Effect::~Effect()
{

}


std::ostream &::gauntlet::operator<<(std::ostream &ostream, const gauntlet::Effect &spell)
{
  ostream << "Particle System based on " << spell.getName() << " template";
  return ostream;
}

