//
// Created by Akash Sant on 15-06-18.
//

#include "Deck.h"

bool Deck::created = false;

Deck* Deck::d = NULL;

const int Deck::CARD_COUNT = 52;

int Deck::seed = 0;

Deck * Deck::getInstance() {
    if (!created) {
        created = true;
        d = new Deck();
        return d;
    } else {
        return d;
    }
}

Deck::Deck() {
    Deck::initDeck();
}

Deck::~Deck() {
    created = false;
}

void Deck::shuffle() {
    static std::mt19937 rng(seed);

    int n = CARD_COUNT;

    while ( n > 1 ) {
        int k = (int) (rng() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    }
}

void Deck::setSeed(int _seed) {
    seed = _seed;
}

void Deck::initDeck() {
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            Card card = Card(Suit(i), Rank(j));
        }
    }
}