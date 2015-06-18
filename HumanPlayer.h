//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_HUMANPLAYER_H
#define STRAIGHTS_HUMANPLAYER_H

#include "Player.h"
#include "PlayerID.h"

class HumanPlayer: public Player {
private:
    Hand * cards_at_hand;
public:
    Hand * getHand() const;
    HumanPlayer(const PlayerID&);
    void addCards(Card*);
    ~HumanPlayer();
};


#endif //STRAIGHTS_HUMANPLAYER_H
