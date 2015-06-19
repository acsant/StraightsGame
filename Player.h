//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_PLAYER_H
#define STRAIGHTS_PLAYER_H

#include <iostream>
#include "Hand.h"
#include "PlayerID.h"
#include "PlayerStrategy.h"

class Player {
private:
    PlayerID player_id;
    bool playsFirst = false;
    Hand * cards_at_hand;
    PlayerStrategy* strategy;
public:
    bool getPlaysFirst() const;
    PlayerID getPlayerId() const;
    explicit Player(const PlayerID&, PlayerStrategy*);
    Hand * getHand() const;
    void addCards(Card*);
    ~Player();
    PlayerStrategy* getStrategy() const;
    void reassessStrategy();
protected:
    void setPlaysFirst();
};

bool operator== (const PlayerID &a, const PlayerID &b);

bool operator!= (const PlayerID &a, const PlayerID &b);

bool operator< (const PlayerID &a, const PlayerID &b);

bool operator<= (const PlayerID &a, const PlayerID &b);

bool operator> (const PlayerID &a, const PlayerID &b);

bool operator>= (const PlayerID &a, const PlayerID &b);

#endif //STRAIGHTS_PLAYER_H
