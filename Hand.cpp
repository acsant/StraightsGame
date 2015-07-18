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
        if (*(*it) == *toRemove) {
            card_collection.erase(it);
            break;
        }

    }

    return toRemove;
}

Hand::~Hand() {
/*
    for (std::vector<Card*>::iterator it = card_collection.begin(); it != card_collection.end(); it++) {
        //delete *it;
        //it = NULL;
    }*/
    card_collection.clear();

}

std::ostream &operator<<(std::ostream & sout, const Hand & hand) {

    for (int i = 0; i < hand.card_collection.size(); i++) {
        Card *c = hand.card_collection[i];
        sout << " " << *c;
    }

    return sout;
}

int Hand::numberOfCards() const {
    return card_collection.size();
}

std::vector<Card *> Hand::getCards() const {
    return card_collection;
}

bool Hand::contains (Card& c) {
    for (int i = 0; i < card_collection.size(); i++) {
        if (*card_collection[i] == c) {
            return true;
        }
    }
    return false;
}

void Hand::removeAll() {

    card_collection.clear();
    int size = card_collection.size();
    int a = size;

}

Card* Hand::findCard(Card &card) {
    for (int i = 0; i < card_collection.size(); i++) {
        if (card_collection[i]->getRank() == card.getRank() && card_collection[i]->getSuit() == card.getSuit()) {
            return card_collection[i];
        }
    }
    return &card;
}
