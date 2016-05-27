//
// World.hh for World in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:51:22 2016 Alexis Trouve
// Last update Fri May 27 16:56:36 2016 Alexis Trouve
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

namespace			gauntlet
{
  namespace			world
  {
    struct			soundGlobal
    {
      int			Id;
      std::pair<double, double>	pos;
      unsigned int		soundId;
      bool			loop;
    };

    struct			effectGlobal
    {
      int			Id;
      std::pair<double, double>	pos;
      unsigned int		effectId;
      short			orientation;
      int			decayTime;
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
      
      //network::PacketFactory	packetFactory;
    private:
      int			getUniqueEffectId();
    public:
      World(GameServer *ngameServer);
      ~World();

      void			loadGame(std::string const & file);
      void			gameLoop();
      void			tester();
      void			applyMoveActor();
      void			applyAI();
      void			notifyDeath(ABody *body);
      void			deleteId(int id);
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
      void			applyCommand(int id, core::Command command);
      ABody			*getBodyById(int id);
      void			animeEntity(int id, unsigned int animeId);
    };
  };
};

#endif
