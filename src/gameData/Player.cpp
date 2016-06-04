//
// Created by jonas_e on 5/9/16.
//

#include <iostream>
#include "Player.hh"

using namespace gauntlet;

Player::Player(int nid, world::World *nworld)
  : Actor(nid, nworld)
{
  playerName = "default";
  score = 0;
}

Player::~Player()
{

}

void    Player::addScore(long addition) {
    this->score += addition;
}

void    Player::use(Item item) {
    if (item.isConsumable())
    {
        this->stats += item.getStats();
        this->inventory.remove(item);
    }
}

void	Player::setPlayerName(const std::string& nplayerName)
{
  playerName = nplayerName;
}

const std::string&	Player::getPlayerName() const
{
  return (playerName);
}

long			Player::getScore() const
{
  return (score);
}

ABody			*Player::clone(int id) const
{
  Player		*player;
  unsigned int	i;

  player = new Player(id, world);
  player->setName(name);
  player->stats.HP = stats.HP;
  player->stats.normalHP = stats.normalHP;
  player->stats.speed = stats.speed;
  player->stats.normalSpeed = stats.normalSpeed;
  player->stats.attackModifier = stats.attackModifier;
  i = 0;
  while (i < spellBook.spellList.size())
    {
      player->spellBook.spellList.push_back(spellBook.spellList[i]);
      ++i;
    }
  player->setCollide(collideActive);
  player->changePos(coord);
  player->changeSize(size);
  player->setMeshId(model);
  player->setTextureId(texture);
  player->setIdle(idle);
  player->death = this->death;
  player->setRunning(running);
  player->changeOrientation(orientation);
  player->setIdAI(idAI);
  return (player);
}

ItemContainer *Player::getInventory() {
  return (&this->inventory);
}


