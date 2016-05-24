//
// Created by jonas_e on 5/21/16.
//

#include "Spell.hh"
#include "World.hh"

gauntlet::Spell::Spell() {
    id = 0;
    name = "";
    range = 0;
    radius = 0;
    damage = 0;
    pattern = CIRCLE;
    angle = 0;
}

gauntlet::Spell::~Spell() {

}

const std::map<gauntlet::Spell::Area , gauntlet::Spell::patternFun> gauntlet::Spell::patternTypes = {
        {CIRCLE, &world::Collider::giveBodyInAreaCircle},
        {CONE, &world::Collider::giveBodyInAreaCone},
        {COLUMN, &world::Collider::giveBodyInAreaCone}
};

void gauntlet::Spell::ApplyDamage(std::list<gauntlet::ABody*> targets, Actor *caster)
{
    Actor*      actor;
    //GameObject* gameObject;
    for (auto target:targets)
    {
        actor = dynamic_cast<Actor*>(target);
        //gameObject = dynamic_cast<GameObject*>(target);
        if (actor != NULL)
            actor->stats.HP -= damage * caster->stats.attackModifier;
        //if (gameObject != NULL)
        //    faire les dégats
    }
}

void gauntlet::Spell::prepare()
{
    //effet sur opening sur coord
    caster->getPos();
    targetedArea = caster->pointInFront(range);
}

void gauntlet::Spell::cast(Actor *caster)
{
    std::list<gauntlet::ABody*> targets;
    targets = (caster->getWorld()->getCollider().*patternTypes.at(pattern))(targetedArea.first, targetedArea.second, caster->getOrientation(), radius, angle); //remplacer les 0 par des variables setées à 0 dans le constructy kthxbye
    ApplyDamage(targets, caster);
}

void gauntlet::Spell::setCaster(Actor* caster)
{
    this->caster = caster;
}

void gauntlet::Spell::setBasicStats(int id, const std::string &name, double range, double radius, long damage, Area pattern) {
    this->id = id;
    this->name = name;
    this->range = range;
    this->radius = radius;
    this->pattern = pattern;
    this->damage = damage;
}

void gauntlet::Spell::setConeAngle(short _angle)
{
    this->angle = _angle;
}






