//
// Created by Akash Sant on 15-06-18.
//

#include "Player.h"
#include "GameManager.h"

int next_id = 1;

Player::Player(const PlayerID& id_, PlayerStrategy* strat): player_id(id_), strategy(strat) {
    cards_at_hand = new Hand();
}

PlayerID Player::getPlayerId() const {
    return player_id;
}

Player::~Player() {
    delete cards_at_hand;
}

bool Player::getPlaysFirst() const {
    return playsFirst;
}

void Player::setPlaysFirst() {
    playsFirst = true;
    GameManager* gm = GameManager::getInstace();
    gm->setFirstPlayer(this);
}

Hand * Player::getHand() const {
    return cards_at_hand;
}

void Player::addCards(Card * c) {
    if (c->getSuit() == SPADE && c->getRank() == SEVEN) {
        setPlaysFirst();
    }
    cards_at_hand->insertCard(c);
}
