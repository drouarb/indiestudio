//
// BodyFactory.hh for BodyFactory in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 15:00:30 2016 Alexis Trouve
// Last update Fri Jun  3 17:18:07 2016 Alexis Trouve
//

#ifndef BODYFACTORY_HH_
# define BODYFACTORY_HH_

#include <vector>
#include "ABody.hh"
#include "Actor.hh"
#include "Player.hh"
#include "Creature.hh"
#include "GameObject.hh"
#include "AbstractAI.hh"
#include "BasicAI.hh"

#define PLAYER_SIZE 22.0

namespace gauntlet
{
  class			BodyFactory
  {
  private:
    std::vector<ABody*>			bodyTab;
    world::World			*world;
    std::vector<world::AbstractAI*>	AIs;
  private:
    int			giveNextId();
    void		fillPlayerTab();
    void		setBarbare();
    void		setElf();
    void		setWizard();
    void		setValkyrie();
    void		fillCreatureTab();
    void		setDraugr();
    void		fillGameObjectTab();
    void		setPorteLight();
    BodyFactory();
  public:
    BodyFactory(world::World *world, std::vector<world::AbstractAI*>& nAIs);
    ~BodyFactory();
    ABody		*giveBody(const std::string& wanted);

      void setKey();
      void setDoor();

      void setSkeleton();

      void setSkeletonWarlord();

      void setSkeletonArcher();

      void setSkeletonWizard();

      void setPotion();

      void setHealthPotion();

      void setSpeedPotion();
  };
};

#endif
