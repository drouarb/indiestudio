//
// Created by jonas_e on 5/9/16.
//

#include "Player.hh"

using namespace gauntlet;

Player::Player()
{

}

Player::~Player()
{

}

void    Player::addScore(long addition) {
    this->score += addition;
}

void    Player::use(Item item) {
    if (item.isConsumable)
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
