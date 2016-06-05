//
// Created by jonas_e on 6/4/16.
//

#ifndef GAUNTLET_MUSICHANDLER_HH
#define GAUNTLET_MUSICHANDLER_HH

#include <string>
#include <map>
#include "World.hh"

namespace gauntlet {
    class MusicHandler {

    public:

        enum		MusicEnum
        {
            PRISON_FIGHT,
            SNAKE_CULT,
            WARRENS_OF_THE_DAMNED,
            STREET_ENCOUNTER,
            NEVER_TOMB,
            DRUID_CIRCLE,
            NORTH_ROAD,
            SOLOMON_AMBUSH,
            HIGH_CAPTAIN,
            FORT_ILLKARD,
            ELK_TRIBE,
            KLAUTH_DEMISE,
            WAR_ZONE,
            ARIBETH_BATTLE,
            LIZARDFOLK_SANCTUARY,
            SOURCE_STONE,
            TRACKING_KOBOLD,
            QUEEN_SHATTERED,
            SIZE
        };
        typedef std::pair<gauntlet::SoundName, int> track;

    private:

        std::map<gauntlet::MusicHandler::MusicEnum, track> trackList;
        unsigned long cooldown;
        int idUsed;
        int timestamp;
        gauntlet::world::World  *world;

    public:

        MusicHandler();
        ~MusicHandler();

        void    stopCurrentTrack();
        void    startRandomTrack();
        bool    isUsed();
    };
};


#endif //GAUNTLET_MUSICHANDLER_HH
