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
            RECTANGLE,
            CIRCLE,
            CONE,
            TRIANGLE,
            ARC
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
    public:
        void                        cast(Actor *caster);
        void                        ApplyDamage(std::list<ABody *> targets, Actor *caster);
        void                        prepare();

        void setId(int id);
        void setName(const std::string &name);
        void setRange(double range);
        void setRadius(double radius);
        void setPattern(Area area);
        void setDamage(long damage);
        void setBasicStats(int id, const std::string &name, double range, double radius, long damage, Area pattern);
    };
};


#endif //GAUNTLET_SPELL_HH
