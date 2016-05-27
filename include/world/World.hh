//
// World.hh for World in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Sun May 22 21:51:22 2016 Alexis Trouve
// Last update Fri May 27 13:21:57 2016 Esteban Lewis
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
      std::vector<int>		effectTab;
      std::vector<int>		soundTab;
      //network::PacketFactory	packetFactory;
    private:
      int			getUniqueEffectId();
    public:
      World(GameServer *ngameServer);
      ~World();

      void			update();
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
      int			triggerEffect(gauntlet::EffectName effect, std::pair<double, double> pos,
					      int decayTime);
      void			stopEffect(int id);
      int			getUniqueSoundId();
      int			playSound(unsigned int soundId, bool loop);
      void			stopSound(int idToStop);
      void			applyCommand(Player & player, core::Command command);
    };
  };
};

#endif
