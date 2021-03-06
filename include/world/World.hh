//
// World.hh for World in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:51:22 2016 Alexis Trouve
//

#ifndef WORLD_HH_
# define WORLD_HH_

#include <string>
#include <list>
#include "EffectName.hh"
#include "ABody.hh"
#include "Actor.hh"
#include "Player.hh"
#include "Creature.hh"
#include "GameObject.hh"
#include "Collider.hh"
#include "BodyFactory.hh"
#include "AbstractAI.hh"
#include "BasicAI.hh"
#include "GameServer.hh"
#include "Conf.hh"
#include "Stopwatch.hh"
#include "IJson.hpp"
#include "MusicHandler.hh"

# define ROUND_DURATION 33
# define AI_PRIORITY 16
# define GATHERING_PRIORITY 17
# define WIN_PRIORITY 29
# define RESPAWN_PRIORITY 64
# define AUTOSHIFT_PRIORITY 11
# define HUD_PRIORITY 15
# define DEATH_COOLDOWN_NB_TURN 455

namespace			gauntlet
{
  namespace			world
  {
    struct			soundGlobal
    {
      int		    Id;
      std::pair<double, double>	pos;
      unsigned int		soundId;
      bool			    loop;
    };

    struct			effectGlobal
    {
      int			Id;
      std::pair<double, double>	pos;
      unsigned int		effectId;
      short			orientation;
      int			decayTime;
    };

    struct			playerDeath
    {
      int			coolDownRespawn;
      Player			*player;
    };

    class			GameServer;
    
    class			World
    {
    private:
      Collider			*collider;
      BodyFactory		*Factory;
      std::vector<gauntlet::world::AbstractAI*>	AIs;
      std::list<ABody*>		bodys;
      double			sizeX;
      double			sizeY;
      std::pair<double, double>	spawnPoint;
      GameServer		*gameServer;
      std::vector<effectGlobal*>	effectTab;
      std::vector<soundGlobal*>	soundTab;
      Stopwatch			stopwatch;
      unsigned long		turn;
      std::pair<double, double>	endPos;
      std::pair<double, double>	endSize;
      std::vector<playerDeath>	deathPlayers;
      std::string		mapAssetName;
      std::string		mapHeightName;
      MusicHandler      musicHandler;
      bool			looper;
    private:
      int			getUniqueEffectId();
    public:
      World(GameServer *ngameServer);
      ~World();

      void			loadGame(std::string const & file);
      bool			saveGame(const std::string &file);
      void			gameLoop();
      void			tester();
      void			applyMoveActor();
      void			applyAI();
      void			notifyDeath(ABody *body);
      void			deleteId(int id, bool deleted);
      int			addNewBody(double xpos, double ypos, const std::string& name, short orientation);
      Collider&			getCollider();
      const std::pair<double, double>&	getSpawnPoint();
      std::list<ABody*>		getBodysByCopy() const;
      std::vector<effectGlobal*>	getEffectByCopy() const;
      std::vector<soundGlobal*>	getSoundByCopy() const;
      void			putEffect(unsigned int effectId, short orient,
					      const std::pair<double, double>& pos);
      int			triggerEffect(gauntlet::EffectName effect, short orient,
					      const std::pair<double, double>& pos, int decayTime);
      int			triggerEffect(gauntlet::EffectName effect,
					      const std::pair<double, double>& pos, int decayTime);
      void			stopEffect(int id);
      int			getUniqueSoundId();
      void			putSound(unsigned int soundId, const std::pair<double, double>& pos);
      int			playSound(unsigned int soundId, bool loop, const std::pair<double, double>& pos);
      void			stopSound(int idToStop);
      void			applyCommand(short angle, int id, core::Command command);
      ABody			*getBodyById(int id);
      void			animeEntity(int id, unsigned int animeId, bool loop);
      unsigned long		getTurn() const;
      void			applyGatheringAndOpening();
      void			checkWin();
      void			checkRespawn();
      void			checkHUD();
      std::string		getMapNames() const;
      std::pair<double, double>	getSize() const;
      void			setLooper(bool nloop);

        JSON::JsonStr doubleToJsonStr(double d);

        JSON::JsonStr angleToJsonStr(int a);

        JSON::JsonStr intToJsonStr(int d);

      MusicHandler  *getMusicHandler();
    };
  };
};

#endif
