//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_COMPUTERPLAYER_H
#define STRAIGHTS_COMPUTERPLAYER_H

#include "Hand.h"

#include "PlayerStrategy.h"
#include "Command.h"

class ComputerPlayer: public PlayerStrategy {

public:
    void play(Command);
    bool isHuman();
    ComputerPlayer();
    ~ComputerPlayer();
};

#endif //STRAIGHTS_COMPUTERPLAYER_H
