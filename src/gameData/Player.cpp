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
