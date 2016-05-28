//
// Created by jonas_e on 5/21/16.
//

#ifndef GAUNTLET_SPELL_HH
#define GAUNTLET_SPELL_HH

#include <map>
#include <list>
#include <graph/EffectName.hh>
#include "AreaType.hh"
#include "ASpell.hh"
#include "ABody.hh"
#include "Actor.hh"
#include "Collider.hh"

namespace gauntlet {
  class Spell {
  public:
    Spell();
    ~Spell();

    typedef std::list<ABody *> (world::Collider::*patternFun)(double, double, short, double, short);

    const static std::map<Area, patternFun> patternTypes;

  protected:
    Actor                       *caster;
    int                         id;
    std::string                 name;
    double                      range;
    double                      radius;
    long                        damage;
    Area	                pattern;
    std::pair<double, double>   targetedArea;
    short                       angle;
    short                       effectOrientation;
    int                         openingEffect;
    int                         endingEffect;
    int                         openingId;
    int                         endingId;
    bool			taunt;
  public:
    void                        cast(Actor *caster);
    void                        ApplyDamage(std::list<ABody *> targets, Actor *caster);
    void                        prepare();
    void                        setBasicStats(int id, const std::string &name, double range,
					      double radius, long damage, Area pattern);
    void                        setCaster(Actor *caster);
    void                        setConeAngle(short id);

    void			setEffect(gauntlet::EffectName opening, gauntlet::EffectName ending);

    long			getDamage() const;
    short			getAngle() const;
    Area			getAreaType() const;
    double			getRadius() const;
    double			getRange() const;
    const std::string&		getName() const;
  };
};


#endif //GAUNTLET_SPELL_HH
