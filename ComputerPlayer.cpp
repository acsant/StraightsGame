//
// Created by Akash Sant on 15-06-18.
//

#include "ComputerPlayer.h"

Hand * ComputerPlayer::getHand() const {
    return cards_at_hand;
}

ComputerPlayer::ComputerPlayer(const PlayerID& id_): Player(id_) { }

void ComputerPlayer::addCards(Card * c) {
    cards_at_hand->insertCard(c);
}

ComputerPlayer::~ComputerPlayer() {
    delete cards_at_hand;
}