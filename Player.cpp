//
// Created by Akash Sant on 15-06-18.
//

#include "Player.h"

int next_id = 1;

Player::Player(const PlayerID& id_): player_id(id_) { }

PlayerID Player::getPlayerId() const {
    return player_id;
}

Player::~Player() {

}