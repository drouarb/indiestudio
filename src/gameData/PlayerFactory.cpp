//
// PlayerFactory.cpp for indie in /home/trouve_b/Desktop/CPP_project/cpp_indie_studio
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed May 11 19:05:59 2016 Alexis Trouve
// Last update Wed May 18 14:19:14 2016 Alexis Trouve
//

#include <iostream>
#include "PlayerFactory.hh"

using namespace gauntlet;

PlayerFactory::PlayerFactory()
{
  fillPlayerTab();
}

PlayerFactory::~PlayerFactory()
{

}

void		PlayerFactory::fillPlayerTab()
{
  playerTab.push_back({BARBARE, &PlayerFactory::giveBarbare});
  playerTab.push_back({ELF, &PlayerFactory::giveElf});
  playerTab.push_back({MAGE, &PlayerFactory::giveMage});
  playerTab.push_back({VALKYRIE, &PlayerFactory::giveValkyrie});
}

Player	*PlayerFactory::giveBarbare(int id)
{
  Player	*player;

  player = new Player(id, -1, -1, SIZE_X_PLAYER, SIZE_Y_PLAYER, 0);
  return (player);
}

Player	*PlayerFactory::giveElf(int id)
{
  Player	*player;

  player = new Player(id, -1, -1, SIZE_X_PLAYER, SIZE_Y_PLAYER, 0);
  return (player);
}

Player	*PlayerFactory::giveMage(int id)
{
  Player	*player;

  player = new Player(id, -1, -1, SIZE_X_PLAYER, SIZE_Y_PLAYER, 0);
  return (player);
}

Player	*PlayerFactory::giveValkyrie(int id)
{
  Player	*player;

  player = new Player(id, -1, -1, SIZE_X_PLAYER, SIZE_Y_PLAYER, 0);
  return (player);
}

Player	*PlayerFactory::givePlayer(BodyEnum type, int id)
{
  unsigned int		i;

  i = 0;
  while (i < playerTab.size())
    {
      if (playerTab[i].type == type)
	return ((this->*playerTab[i].givePtr)(id));
      ++i;
    }
  return (NULL);
}
