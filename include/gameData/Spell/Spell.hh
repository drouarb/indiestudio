//
// Created by jonas_e on 5/21/16.
//

#ifndef GAUNTLET_SPELL_HH
#define GAUNTLET_SPELL_HH

#include <map>
#include <list>
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
        enum 		Area
        {
            WALL,
            COLUMN,
            CIRCLE,
            CONE,
            TRIANGLE
        };
        const static std::map<Area, patternFun> patternTypes;

    protected:
        Actor                       *caster;
        int                         id;
        std::string                 name;
        double                      range;
        double                      radius;
        long                        damage;
        Area	                    pattern;
        std::pair<double, double>   targetedArea;
        short                       angle;
    public:
        void                        cast(Actor *caster);
        void                        ApplyDamage(std::list<ABody *> targets, Actor *caster);
        void                        prepare();
        void                        setBasicStats(int id, const std::string &name, double range, double radius, long damage, Area pattern);
        void                        setCaster(Actor *caster);

        void setConeAngle(short id);
    };
};


#endif //GAUNTLET_SPELL_HH
