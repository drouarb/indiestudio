//
// Created by jonas_e on 5/9/16.
//

#include "Player.hh"

using namespace gauntlet;

Player::Player(bool ncollide, int nid, double posx, double posy,
	       double sizex, double sizey, short norient)
  : Actor(ncollide, nid, posx, posy, sizex, sizey, norient)
{
}

Player::Player(int nid, double posx, double posy,
	       double sizex, double sizey, short norient)
  : Actor(nid, posx, posy, sizex, sizey, norient)
{
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
/*
void    gauntlet::Player::equip(Item item) {
    if (item.notEquiped)
    {
        this->stats += item.getStats();
    }
}
*/
