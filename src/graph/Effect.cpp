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
  this->_particleSystem = ogreUI->getSceneManager()->createParticleSystem(name, *this->name);
  if (this->_particleSystem == NULL)
    {
      throw std::runtime_error("Template " + name + " not found");
    }
  Ogre::SceneNode* particleNode = ogreUI->getSceneManager()->getRootSceneNode()->createChildSceneNode(name + "scene");
  particleNode->setPosition((Ogre::Vector3(static_cast<float>(coord.first), ogreUI->getHeightAt(coord.first, coord.second), static_cast<float >(coord.second))));
  particleNode->setScale(particleNode->getScale() / _EFFECT_DIVIDE_SIZE);
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

