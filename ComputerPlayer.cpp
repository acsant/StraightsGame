//
// Created by Akash Sant on 15-06-18.
//

#include "ComputerPlayer.h"

Hand * ComputerPlayer::getHand() const {
    return cards_at_hand;
}

ComputerPlayer::ComputerPlayer(const PlayerID& id_): Player(id_) {
    cards_at_hand = new Hand();
}

void ComputerPlayer::addCards(Card * c) {
    if (c->getSuit() == SPADE && c->getRank() == SEVEN) {
        setPlaysFirst();
    }
    cards_at_hand->insertCard(c);
}

ComputerPlayer::~ComputerPlayer() {
    delete cards_at_hand;
}