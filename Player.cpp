//
// Created by Akash Sant on 15-06-18.
//

#include "Player.h"

Player::Player(std::string name_, int id): name(name_), player_id(id) { }

std::string Player::getName() const {
    return name;
}

int Player::getPlayerId() const {
    return player_id;
}

Hand * Player::getHand() const {
    return cards_at_hand;
}

Player::~Player() {
    delete cards_at_hand;
}