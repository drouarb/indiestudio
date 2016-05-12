//
// PlayerFactory.hh for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 18:36:12 2016 Alexis Trouve
// Last update Thu May 12 17:10:32 2016 Alexis Trouve
//

#ifndef PLAYERFACT_HH_
# define PLAYERFACT_HH_

#include <vector>
#include "FactoryData.hh"
#include "Player.hh"

namespace gauntlet
{

  class	PlayerFactory;
  
  struct	PlayerStruct
  {
    gauntlet::BodyEnum		type;
    gauntlet::Player	*(gauntlet::PlayerFactory::*givePtr)(int id);
  };

  class	PlayerFactory
  {
  private:
    std::vector<PlayerStruct>	playerTab;
  private:
    void				fillPlayerTab();

    gauntlet::Player	*giveBarbare(int id);
    gauntlet::Player	*giveElf(int id);
    gauntlet::Player	*giveMage(int id);
    gauntlet::Player	*giveValkyrie(int id);
  public:
    PlayerFactory();
    ~PlayerFactory();
    gauntlet::Player	*givePlayer(gauntlet::BodyEnum type, int id);
  };
};

#endif
