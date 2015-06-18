//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_HAND_H
#define STRAIGHTS_HAND_H

#include "Card.h"
#include <iostream>
#include <vector>

class Hand {
private:
    std::vector<Card*> card_collection;
public:
    Hand();
    void insertCard(Card*);
    Card * removeCard(Card*);
    ~Hand();
};

#endif //STRAIGHTS_HAND_H
