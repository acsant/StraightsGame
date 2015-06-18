//
// Created by Akash Sant on 15-06-18.
//

#ifndef STRAIGHTS_DECK_H
#define STRAIGHTS_DECK_H

#include <stddef.h>
#include <vector>
#include "Card.h"
#include <random>

class Deck {
private:
    static bool created;
    static const int CARD_COUNT;
    static Deck * d;
    static int seed;
    Deck();
    std::vector<Card*> cards_;
public:
    static Deck * getInstance();
    void shuffle();
    void setSeed(int);
    ~Deck();
};

#endif //STRAIGHTS_DECK_H
