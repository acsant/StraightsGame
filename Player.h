//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_PLAYER_H
#define STRAIGHTS_PLAYER_H

#include <iostream>
#include "Hand.h"

class Player {
private:
    std::string name;
    int player_id;
    Hand * cards_at_hand;
public:
    std::string getName() const;
    int getPlayerId() const;
    Player(std::string, int);
    Hand * getHand() const;
    ~Player();
};

#endif //STRAIGHTS_PLAYER_H
