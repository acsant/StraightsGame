//
// Created by Akash Sant on 15-06-18.
//

#include "PlayerID.h"

int PlayerID::next_id = 1;
PlayerID::PlayerID() {
    if (next_id > max_num) {
        exit(1);
    }
    player_id = next_id++;
}

PlayerID::PlayerID(int id_) {
    if (id_ > max_num || id_ < 1) {
        exit(1);
    }
    player_id = id_;
}