//
// Created by Akash Sant on 15-06-18.
//


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
    GameManager* gm = GameManager::getInstance();
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

PlayerStrategy *Player::getStrategy() const {
    return strategy;
}

void Player::discard(Card *card) {
    discards.push_back(card);
}

void Player::reassessStrategy() {
    delete strategy;
    strategy = new ComputerPlayer;
}

void Player::awardPoints(int points) {
    GameManager* gm = GameManager::getInstance();
    roundScore[gm->getCurrentRound()] = roundScore[gm->getCurrentRound()] + points;
}

std::vector<Card *> Player::getDiscards() const {
    return discards;
}

std::vector<int> Player::getRoundScores() const {
    return roundScore;
}

void Player::setGameScore(int totalScore) {
    gameScore = totalScore;
}

int Player::getGameScore() const {
    return gameScore;
}