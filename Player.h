//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_PLAYER_H
#define STRAIGHTS_PLAYER_H

#include <iostream>
#include "Hand.h"
#include "PlayerID.h"
#include "PlayerStrategy.h"
#include "ComputerPlayer.h"

class Player {
private:
    PlayerID player_id;
    bool playsFirst;
    Hand * cards_at_hand;
    PlayerStrategy* strategy;
    std::vector<Card*> discards;
    int gameScore;

    std::vector<int> roundScore;
public:
    bool getPlaysFirst() const;
    void awardPoints(int points);
    std::vector<Card*> getDiscards() const;
    void discard(Card*);
    PlayerID getPlayerId() const;
    explicit Player(const PlayerID&, PlayerStrategy*);
    Hand * getHand() const;
    void addCards(Card*);
    ~Player();
    PlayerStrategy* getStrategy() const;
    void reassessStrategy();
    void setPlaysFirst();
    int getGameScore() const;
    std::vector<int> getRoundScores() const;
    void setGameScore(int);
};

bool operator== (const PlayerID &a, const PlayerID &b);

bool operator!= (const PlayerID &a, const PlayerID &b);

bool operator< (const PlayerID &a, const PlayerID &b);

bool operator<= (const PlayerID &a, const PlayerID &b);

bool operator> (const PlayerID &a, const PlayerID &b);

bool operator>= (const PlayerID &a, const PlayerID &b);

#endif //STRAIGHTS_PLAYER_H