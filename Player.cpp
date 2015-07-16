//
// Created by Akash Sant on 15-06-18.
//


#include "GameManager.h"
#include "MemCheck.h"

int next_id = 1;

Player::Player(const PlayerID& id_, PlayerStrategy* strat): player_id(id_), strategy(strat) {
    MEM_ON();
    cards_at_hand = new Hand();
    playsFirst = false;
    roundScore.push_back(0);
    gameScore = 0;
    MEM_OFF();
}

PlayerID Player::getPlayerId() const {
    return player_id;
}

Player::~Player() {
    MEM_ON();
    delete cards_at_hand;
    delete strategy;
    //for (std::vector<Card*>::iterator it = discards.begin(); it != discards.end(); it++) {
      //  delete it;
    //}
    for (int i = 0; i < discards.size(); i++) {
        delete discards[i];
    }
    MEM_OFF();
}

bool Player::getPlaysFirst() const {
    return playsFirst;
}

void Player::setPlaysFirst() {
    MEM_ON();
    playsFirst = true;
    GameManager* gm = GameManager::getInstance();
    gm->setFirstPlayer(this);
    MEM_OFF();
}

Hand * Player::getHand() const {
    return cards_at_hand;
}

void Player::addCards(Card * c) {
    MEM_ON();
    if (c->getSuit() == SPADE && c->getRank() == SEVEN) {
        setPlaysFirst();
    }
    cards_at_hand->insertCard(c);
    MEM_OFF();
}

PlayerStrategy *Player::getStrategy() const {
    return strategy;
}

void Player::discard(Card *card) {
    discards.push_back(card);
}

void Player::reassessStrategy() {
    MEM_ON();
    delete strategy;
    strategy = new ComputerPlayer;
    MEM_OFF();
}

void Player::awardPoints(int points) {
    MEM_ON();
    GameManager* gm = GameManager::getInstance();
    int newPoints = roundScore[gm->getCurrentRound() - 1] + points;
    roundScore[gm->getCurrentRound() - 1] = newPoints;
    MEM_OFF();
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
    MEM_ON();
    cards_at_hand->removeAll();
    discards.clear();
    MEM_OFF();
}


void Player::addRound() {
    roundScore.push_back(0);

}
