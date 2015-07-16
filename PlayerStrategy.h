//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_PLAYERSTRATEGY_H
#define STRAIGHTS_PLAYERSTRATEGY_H
#include "Command.h"

class PlayerStrategy {
public:
    virtual void play(Command) = 0;
};

#endif //STRAIGHTS_PLAYERSTRATEGY_H
