//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_PLAYERID_H
#define STRAIGHTS_PLAYERID_H

#include <stdlib.h>

class PlayerID {
private:
    static int const max_num = 4;
    static int next_id;
public:
    int player_id;
    PlayerID();
    PlayerID(int);
};

#endif //STRAIGHTS_PLAYERID_H
