//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_COMPUTERPLAYER_H
#define STRAIGHTS_COMPUTERPLAYER_H

#include "Hand.h"
#include "Player.h"
#include "PlayerStrategy.h"

class ComputerPlayer: public PlayerStrategy {

public:
    void play();
    ComputerPlayer();
    ~ComputerPlayer();
};

#endif //STRAIGHTS_COMPUTERPLAYER_H
