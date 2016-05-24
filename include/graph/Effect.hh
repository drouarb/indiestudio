//
// Created by greg on 22/05/16.
//

#pragma once

#include <map>
#include <OgreParticleSystem.h>
#include <graph/OgreUI.hh>

class OgreUI;

namespace gauntlet
{

  enum EffectName : int
  {
    ATOMIC,
    BLIND,
    BLINK,
    BUBBLES,
    BUMPY,
    CELLS,
    CLASSIC,
    CROSS,
    EXPLOSION,
    FAIRY,
    FULLSPECTRUM,
    GALAXY,
    LINES,
    MULTI_EMITTERS,
    PLASMA,
    RAIN,
    SNOW,
    SPIRAL,
    SUPERNOVA
  };

  class Effect
  {
   public:
    std::map<EffectName, std::string> _effectName = {
	    {ATOMIC, "Atomic"},
	    {BLIND, "Blind"},
	    {BLINK, "Blink"},
	    {BUBBLES, "Bubbles"},
	    {BUMPY, "0BumpyShader"},
	    {CLASSIC, "Classic"},
	    {CELLS, "Cells"},
	    {CROSS, "Cross"},
	    {EXPLOSION, "Explosion"},
	    {FAIRY, "Fairy"},
	    {FULLSPECTRUM, "Fullspectrum"},
	    {GALAXY, "Galaxy"},
	    {LINES, "Lines"},
	    {MULTI_EMITTERS, "MultiEmitters"},
	    {PLASMA, "Plasma"},
	    {RAIN, "Rain"},
	    {SNOW, "Snow"},
	    {SPIRAL, "Spiral"},
	    {SUPERNOVA, "Supernova"},
    };

   private:
    Effect();
    Effect(Effect const &);

    std::string const *name;
    Ogre::ParticleSystem *_particleSystem;

   public:
    Effect(OgreUI *ogreUI, EffectName type, const std::string &name, std::pair<double, double> coord,int percent);
    ~Effect();
    Ogre::ParticleSystem *getParticleSystem() const;
    std::string const &getName() const;
  };

  std::ostream &operator<<(std::ostream &, const Effect &);

}
