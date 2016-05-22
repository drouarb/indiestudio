//
// Created by jonas_e on 5/21/16.
//

#include "Spell.hh"
#include "World.hh"

gauntlet::Spell::Spell() {

}

gauntlet::Spell::~Spell() {

}

const std::map<gauntlet::Spell::Area , gauntlet::Spell::patternFun> gauntlet::Spell::patternTypes = {
        {CIRCLE, &world::Collider::giveBodyInAreaCircle},
        {CONE, &world::Collider::giveBodyInAreaCone}
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

void gauntlet::Spell::cast(Actor *caster) {
    std::list<gauntlet::ABody*> targets;
    targets = (caster->getWorld()->getCollider().*patternTypes.at(pattern))(targetedArea.first, targetedArea.second, 0, radius, 0); //remplacer les 0 par des variables setées à 0 dans le constructy kthxbye
    ApplyDamage(targets, caster);
}

void gauntlet::Spell::setId(int id) {
    this->id = id;
}

void gauntlet::Spell::setName(const std::string &name) {
    this->name = name;
}

void gauntlet::Spell::setRange(double range) {
    this->range = range;
}

void gauntlet::Spell::setRadius(double radius) {
    this->radius = radius;
}

void gauntlet::Spell::setDamage(long damage) {
    this->damage = damage;
}

void gauntlet::Spell::setPattern(Area pattern) {
    this->pattern = pattern;
}

void gauntlet::Spell::setBasicStats(int id, const std::string &name, double range, double radius, long damage, Area pattern) {
    this->id = id;
    this->name = name;
    this->range = range;
    this->radius = radius;
    this->pattern = pattern;
    this->damage = damage;
}






