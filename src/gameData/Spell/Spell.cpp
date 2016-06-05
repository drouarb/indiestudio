//
// Created by jonas_e on 5/21/16.
//

#include <gameData/SoundName.hh>
#include <iostream>
#include <stdlib.h>
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
    specialAnimation = animations::AnimationsListJson::DOOR_OPEN;
}

gauntlet::Spell::~Spell() {

}

const std::map<gauntlet::Area , gauntlet::Spell::patternFun> gauntlet::Spell::patternTypes = {
        {CIRCLE, &world::Collider::giveBodyInAreaCircle},
        {CONE, &world::Collider::giveBodyInAreaCone},
        {COLUMN, &world::Collider::giveBodyInAreaCone},
        {FLIGHT_PATH, &world::Collider::giveBodyInAreaflightPath},
        {SELF_CIRCLE, &world::Collider::giveBodyInAreaCircleWithCaster}
};

void gauntlet::Spell::ApplyDamage(std::list<gauntlet::ABody*> targets, Actor *caster)
{
    Actor*      actor;
    Player*     player;
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
                if ((player = dynamic_cast<Player*>(caster)) != NULL)
                    player->score += 100 * actor->stats.attackModifier;
                actor->stats.HP = 0;
                actor->desu();
                actor->getWorld()->notifyDeath(actor);
            }
        }
    }
}

void gauntlet::Spell::prepare(Actor *actor)
{
    if (openingEffect > -1)
        openingId = caster->getWorld()->triggerEffect((EffectName) openingEffect, actor->getOrientation(), actor->getPos(), 1000);
    unsigned int sound = caster->soundEffect[ABody::ATTACK].at(rand() % caster->soundEffect[ABody::ATTACK].size());
    caster->getWorld()->playSound(sound, false, actor->getPos());
    if (actor->getMove())
        actor->setMove();
    //lancer Animation sur caster
    if (specialAnimation == animations::AnimationsListJson::DOOR_OPEN)
        caster->getWorld()->animeEntity(actor->getId(), caster->animations[ABody::ATTACK].at(rand() % caster->animations[ABody::ATTACK].size()), false);
    else
        caster->getWorld()->animeEntity(actor->getId(), specialAnimation, false);
    targetedArea = actor->pointInFront(range);
    if (targetedArea.first > caster->getWorld()->getSize().first)
        targetedArea.first = caster->getWorld()->getSize().first - 1;
    if (targetedArea.second > caster->getWorld()->getSize().second)
        targetedArea.second = caster->getWorld()->getSize().second - 1;
    if (targetedArea.first < 0)
        targetedArea.first = 1;
    if (targetedArea.second < 0)
        targetedArea.second = 1;
}

void gauntlet::Spell::cast(Actor *actor)
{
    std::list<gauntlet::ABody*> targets;

    if (endingEffect > -1)
        endingId = actor->getWorld()->triggerEffect((EffectName) endingEffect, actor->getOrientation(), actor->pointInFront(range), 1000);
    targets = (actor->getWorld()->getCollider().*patternTypes.at(pattern))(targetedArea.first, targetedArea.second, actor->getOrientation(), radius, angle); //remplacer les 0 par des variables setées à 0 dans le constructy kthxbye
    if (targets.size() > 0) {
        actor->getWorld()->playSound(soundEffect, false, targetedArea);
        actor->getWorld()->getMusicHandler()->startRandomTrack();
    }
    if ((rand() % 100) < (100 * actor->stats.attackModifier))
        ApplyDamage(targets, actor);
    actor->setCooldown(castTime);
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

void gauntlet::Spell::setBasicStats(int id, const std::string &name, double range,
				    double radius, long damage, Area pattern,
				    unsigned int effect, unsigned long castTime)
{
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

void            gauntlet::Spell::setSpecialAnimation(animations::AnimationsListJson _animation)
{
    specialAnimation = _animation;
}

