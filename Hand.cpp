//
// Created by Akash Sant on 15-06-18.
//

#include "Hand.h"

Hand::Hand() {
    card_collection = std::vector<Card*>();
}

void Hand::insertCard(Card* toInsert) {
    card_collection.push_back(toInsert);
}

Card * Hand::removeCard(Card* toRemove) {
    for (std::vector<Card*>::iterator it = card_collection.begin(); it != card_collection.end(); it++) {
        if ((*it) == toRemove) {

            card_collection.erase(it);
        }
    }
    return toRemove;
}

Hand::~Hand() {
    for (std::vector<Card*>::iterator it = card_collection.begin(); it != card_collection.end(); it++) {
        delete (*it);
    }
}

std::ostream &operator<<(std::ostream & sout, const Hand & hand) {
    for (int i = 0; i < hand.card_collection.size(); i++) {
        sout << *(hand.card_collection[i]) << " ";
    }
    return sout;
}

int Hand::numberOfCards() const {
    return card_collection.size();
}
