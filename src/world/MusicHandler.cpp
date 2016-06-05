//
// Created by jonas_e on 6/4/16.
//

#include <gameData/SoundName.hh>
#include <iostream>
#include "MusicHandler.hh"
#include "World.hh"

std::map<gauntlet::MusicHandler::MusicEnum, gauntlet::MusicHandler::track> gauntlet::MusicHandler::trackList {
        {gauntlet::MusicHandler::PRISON_FIGHT, gauntlet::MusicHandler::track{gauntlet::SoundName::PRISON_FIGHT, 90}},
        {gauntlet::MusicHandler::SNAKE_CULT, gauntlet::MusicHandler::track{gauntlet::SoundName::SNAKE_CULT, 115}},
        {gauntlet::MusicHandler::WARRENS_OF_THE_DAMNED, gauntlet::MusicHandler::track{gauntlet::SoundName::WARRENS_OF_THE_DAMNED, 96}},
        {gauntlet::MusicHandler::STREET_ENCOUNTER, gauntlet::MusicHandler::track{gauntlet::SoundName::STREET_ENCOUNTER, 93}},
        {gauntlet::MusicHandler::NEVER_TOMB, gauntlet::MusicHandler::track{gauntlet::SoundName::NEVER_TOMB, 91}},
        {gauntlet::MusicHandler::DRUID_CIRCLE, gauntlet::MusicHandler::track{gauntlet::SoundName::DRUID_CIRCLE, 93}},
        {gauntlet::MusicHandler::NORTH_ROAD, gauntlet::MusicHandler::track{gauntlet::SoundName::NORTH_ROAD, 93}},
        {gauntlet::MusicHandler::SOLOMON_AMBUSH, gauntlet::MusicHandler::track{gauntlet::SoundName::SOLOMON_AMBUSH, 103}},
        {gauntlet::MusicHandler::HIGH_CAPTAIN, gauntlet::MusicHandler::track{gauntlet::SoundName::HIGH_CAPTAIN, 84}},
        {gauntlet::MusicHandler::FORT_ILLKARD, gauntlet::MusicHandler::track{gauntlet::SoundName::FORT_ILLKARD, 93}},
        {gauntlet::MusicHandler::ELK_TRIBE, gauntlet::MusicHandler::track{gauntlet::SoundName::ELK_TRIBE, 99}},
        {gauntlet::MusicHandler::KLAUTH_DEMISE, gauntlet::MusicHandler::track{gauntlet::SoundName::KLAUTH_DEMISE, 98}},
        {gauntlet::MusicHandler::WAR_ZONE, gauntlet::MusicHandler::track{gauntlet::SoundName::WAR_ZONE, 102}},
        {gauntlet::MusicHandler::ARIBETH_BATTLE, gauntlet::MusicHandler::track{gauntlet::SoundName::ARIBETH_BATTLE, 96}},
        {gauntlet::MusicHandler::LIZARDFOLK_SANCTUARY, gauntlet::MusicHandler::track{gauntlet::SoundName::LIZARDFOLK_SANCTUARY, 108}},
        {gauntlet::MusicHandler::SOURCE_STONE, gauntlet::MusicHandler::track{gauntlet::SoundName::SOURCE_STONE, 96}},
        {gauntlet::MusicHandler::TRACKING_KOBOLD, gauntlet::MusicHandler::track{gauntlet::SoundName::TRACKING_KOBOLD, 135}},
        {gauntlet::MusicHandler::QUEEN_SHATTERED, gauntlet::MusicHandler::track{gauntlet::SoundName::QUEEN_SHATTERED, 122}}
};

gauntlet::MusicHandler::MusicHandler() {
    this->cooldown = 0;
    this->idUsed = 0;
}

gauntlet::MusicHandler::~MusicHandler() {

}

void gauntlet::MusicHandler::stopCurrentTrack() {
    world->stopSound(idUsed);
    idUsed = 0;
    cooldown = 0;
}

bool gauntlet::MusicHandler::isUsed() {
    std::cerr << "isused" << std::endl;
    return (cooldown < world->getTurn());
}

void gauntlet::MusicHandler::startRandomTrack() {
    if (isUsed())
    {
        std::cerr << "notused" << std::endl;
        MusicEnum music = (MusicEnum) (rand() % trackList.size());
        std::cerr << "music:"<<music << std::endl;
        track currentTrack = trackList.at(music);
        std::cerr << "track:"<< currentTrack.first << " " << currentTrack.second << std::endl;
        cooldown = world->getTurn() + ((currentTrack.second + 5) * ROUND_DURATION);
        std::cerr << "cooldown:" << cooldown << std::endl;
        idUsed = world->playSound(currentTrack.first, false, std::pair<double, double>(1,1));
        std::cerr << "id:" << idUsed << std::endl;
    }
}

void gauntlet::MusicHandler::setWorld(world::World *_world) {
    world = _world;
}









