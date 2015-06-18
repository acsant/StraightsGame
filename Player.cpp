//
// Created by Akash Sant on 15-06-18.
//

#include "Player.h"
#include "GameManager.h"

int next_id = 1;

Player::Player(const PlayerID& id_): player_id(id_) { }

PlayerID Player::getPlayerId() const {
    return player_id;
}

Player::~Player() {

}

bool Player::getPlaysFirst() const {
    return playsFirst;
}

void Player::setPlaysFirst() {
    playsFirst = true;
    GameManager* gm = GameManager::getInstace();
    gm->setFirstPlayer(this);
}

