//
// Created by Akash Sant on 15-06-18.
//


#include "GameManager.h"

int next_id = 1;

Player::Player(const PlayerID& id_, PlayerStrategy* strat): player_id(id_), strategy(strat) {
    cards_at_hand = new Hand();
    playsFirst = false;
    roundScore.push_back(0);
}

PlayerID Player::getPlayerId() const {
    return player_id;
}

Player::~Player() {
    delete cards_at_hand;
    delete strategy;
    for (std::vector<Card*>::iterator it = discards.begin(); it != discards.end(); it++) {
        delete *it;
    }
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
    int newPoints = roundScore[gm->getCurrentRound() - 1] + points;
    roundScore[gm->getCurrentRound() - 1] = newPoints;
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

void Player::removePlaysFirst() {
    playsFirst = false;
}

void Player::resetPlayer() {
    cards_at_hand->removeAll();
    discards.clear();
}


void Player::addRound() {
    roundScore.push_back(0);

}
