//
// Created by jonas_e on 5/9/16.
//

#include "Player.hh"

gauntlet::Player::Player() {
}

gauntlet::Player::~Player() {
}

void    gauntlet::Player::addScore(long addition) {
    this->score += addition;
}

void    gauntlet::Player::use(Item item) {
    if (item.isConsumable)
    {
        this->stats += item.getStats();
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