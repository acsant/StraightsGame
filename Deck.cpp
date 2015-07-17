//
// Created by Akash Sant on 15-06-18.
//

#include "Deck.h"
#include "MemCheck.h"

bool Deck::created = false;

Deck* Deck::d = NULL;

const int Deck::CARD_COUNT = 52;

int Deck::seed = 0;

Deck * Deck::getInstance() {
    MEM_ON();
    if (!created) {
        created = true;
        d = new Deck();
        return d;
    } else {
        return d;
    }
    MEM_OFF();
}

Deck::Deck() {
    Deck::initDeck();
}

Deck::~Deck() {
    MEM_ON();
    created = false;
    /*for (std::vector<Card*>::iterator it = cards_.begin(); it != cards_.end(); it++) {
        //cards_.erase(it);
        delete it;
    }*/
    for (int i = 0; i < cards_.size(); i++) {
        delete cards_[i];
    }
    cards_.clear();
    MEM_OFF();
    //delete d;
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
    MEM_ON();
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            Card* card = new Card(Suit(i), Rank(j));
            cards_.push_back(card);
        }
    }
    MEM_OFF();
}

std::vector<Card*> Deck::getCards() {
    return cards_;
}

std::ostream &operator<<(std::ostream & sout, const Deck & d) {
    MEM_ON();
    Deck* deckInstance = d.getInstance();
    for (int i = 0; i < 52; i++) {
        sout << deckInstance->getCards().at(i) << " ";
    }
    MEM_OFF();
    return sout;
}
