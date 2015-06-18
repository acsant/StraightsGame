//
// Created by Akash Sant on 15-06-18.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const PlayerID & id_): Player(id_) {
    cards_at_hand = new Hand();
}

Hand * HumanPlayer::getHand() const {
    return cards_at_hand;
}

void HumanPlayer::addCards(Card * c) {
    cards_at_hand->insertCard(c);
}

HumanPlayer::~HumanPlayer() {
    delete cards_at_hand;
}