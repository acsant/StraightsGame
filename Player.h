//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_PLAYER_H
#define STRAIGHTS_PLAYER_H

#include <iostream>
#include "Hand.h"
#include "PlayerID.h"

class Player {
private:
    PlayerID player_id;
    bool playsFirst = false;
public:
    virtual void addCards(Card*) = 0;
    bool getPlaysFirst() const;
    PlayerID getPlayerId() const;
    explicit Player(const PlayerID&);
    ~Player();
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
