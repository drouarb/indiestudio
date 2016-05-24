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
    ATOMIC = 0,
    BLIND = 1,
    BLINK = 2,
    BUBBLES = 3,
    BUMPY = 4,
    CELLS = 5,
    CLASSIC = 6,
    CROSS = 7,
    EXPLOSION = 8,
    FAIRY = 9,
    FULLSPECTRUM = 10,
    GALAXY 11,
    LINES = 12,
    MULTI_EMITTERS = 13,
    PLASMA = 14,
    RAIN = 15,
    SNOW = 16,
    SPIRAL = 17,
    SUPERNOVA = 18
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
