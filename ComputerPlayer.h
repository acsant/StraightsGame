//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_COMPUTERPLAYER_H
#define STRAIGHTS_COMPUTERPLAYER_H

#include "Hand.h"
#include "Player.h"

class ComputerPlayer: public Player {
private:
    Hand * cards_at_hand;
public:
    Hand * getHand() const;
    ComputerPlayer(const PlayerID&);
    void addCards(Card*);
    ~ComputerPlayer();
};

#endif //STRAIGHTS_COMPUTERPLAYER_H
