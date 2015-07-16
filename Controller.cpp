//
// Created by Akash Sant on 15-07-15.
//

#include "Controller.h"
#include "GameManager.h"

Controller::Controller(GameManager* gm): gm_(gm) { }

void Controller::newGameButtonClicked(std::vector<Glib::ustring> player_types) {
    gm_->addPlayersToGame(player_types);
}

void Controller::setSeed(int seed) {
    gm_->setSeed(seed);
}

void Controller::play_card(int index) {
    std::vector<Card*> current_hand = gm_->getCurrentPlayer()->getHand()->getCards();
    Card card = *current_hand.at(index);
    Command c;
    if (gm_->has_legal()) {
        c = Command::Command(PLAY, card);
    } else {
        c = Command::Command(DISCARD, card);

    }
    gm_->play_card(c);
}


void Controller::setNextPlayer() {
    gm_->setNextPlayer();

}
