//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_HUMANPLAYER_H
#define STRAIGHTS_HUMANPLAYER_H

#include "Player.h"
#include "PlayerID.h"
#include "PlayerStrategy.h"
#include "Command.h"

class HumanPlayer: public PlayerStrategy {
public:
    void play(Command);
    HumanPlayer();
    ~HumanPlayer();
};


#endif //STRAIGHTS_HUMANPLAYER_H
