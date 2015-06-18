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
public:
    virtual void addCards(Card*) = 0;
    PlayerID getPlayerId() const;
    explicit Player(const PlayerID&);
    ~Player();
};

#endif //STRAIGHTS_PLAYER_H
