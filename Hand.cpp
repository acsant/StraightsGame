//
// Created by Akash Sant on 15-06-18.
//

#include "Hand.h"

Hand::Hand() { }

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
