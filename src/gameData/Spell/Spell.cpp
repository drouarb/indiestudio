//
// Created by jonas_e on 5/21/16.
//

#include <gameData/SoundName.hh>
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
    openingEffect = -1;
    endingEffect = -1;
    effectOrientation = 0;
}

gauntlet::Spell::~Spell() {

}

const std::map<gauntlet::Area , gauntlet::Spell::patternFun> gauntlet::Spell::patternTypes = {
        {CIRCLE, &world::Collider::giveBodyInAreaCircle},
        {CONE, &world::Collider::giveBodyInAreaCone},
        {COLUMN, &world::Collider::giveBodyInAreaCone},
        {FLIGHT_PATH, &world::Collider::giveBodyInAreaflightPath}
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
        {
            actor->stats.HP -= damage * caster->stats.attackModifier;
            if (actor->stats.HP <= 0)
            {
                actor->setCollide(false);
                actor->getWorld()->notifyDeath(actor);
            }
        }
        //if (gameObject != NULL)
        //    faire les dégats
    }
}

void gauntlet::Spell::prepare()
{
    if (openingEffect > -1)
        openingId = caster->getWorld()->triggerEffect((EffectName) openingEffect, caster->getOrientation(), caster->getPos(), 1000);
    unsigned int sound = caster->soundEffect[ABody::ATTACK_SOUND].at(rand() % caster->soundEffect[ABody::ATTACK_SOUND].size());
    caster->getWorld()->playSound(sound, false, caster->getPos());
    //lancer animation sur caster
    targetedArea = caster->pointInFront(range);
}

void gauntlet::Spell::cast(Actor *caster)
{
    std::list<gauntlet::ABody*> targets;
    if (endingEffect > -1)
        endingId = caster->getWorld()->triggerEffect((EffectName) endingEffect, caster->getOrientation(), caster->getPos(), 1000);
    targets = (caster->getWorld()->getCollider().*patternTypes.at(pattern))(targetedArea.first, targetedArea.second, caster->getOrientation(), radius, angle); //remplacer les 0 par des variables setées à 0 dans le constructy kthxbye
    if (targets.size() > 0) {
        caster->getWorld()->playSound(soundEffect, false, targetedArea);
    }
    ApplyDamage(targets, caster);
    caster->setCooldown(castTime);
}

void gauntlet::Spell::setCaster(Actor* caster)
{
    this->caster = caster;
}

void gauntlet::Spell::setEffect(EffectName opening, EffectName ending)
{
    openingEffect = opening;
    endingEffect = ending;
}

void gauntlet::Spell::setBasicStats(int id, const std::string &name, double range, double radius, long damage, Area pattern,
                                    unsigned int effect, unsigned long castTime) {
    this->id = id;
    this->name = name;
    this->range = range;
    this->radius = radius;
    this->pattern = pattern;
    this->damage = damage;
    this->soundEffect = effect;
    this->castTime = ((castTime * 10) / ROUND_DURATION);
}

void gauntlet::Spell::setConeAngle(short _angle)
{
    this->angle = _angle;
}

long			gauntlet::Spell::getDamage() const
{
  return (damage);
}

short			gauntlet::Spell::getAngle() const
{
  return (angle);
}

gauntlet::Area		gauntlet::Spell::getAreaType() const
{
  return (pattern);
}

double			gauntlet::Spell::getRadius() const
{
  return (radius);
}

double			gauntlet::Spell::getRange() const
{
  return (range);
}

const std::string&	gauntlet::Spell::getName() const
{
  return (name);
}


