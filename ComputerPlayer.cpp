//
// Created by Akash Sant on 15-06-18.
//

#include "ComputerPlayer.h"
#include "GameManager.h"


ComputerPlayer::ComputerPlayer() {

}
//implementation of the play function using the strategy design pattern
void ComputerPlayer::play() {
    GameManager* gm = GameManager::getInstance();
    bool legalExists = false;
    Card* currentCard;
    //iterate through the player's hand and check if a legal play exists
    for (int k = 0; k < gm->getCurrentPlayer()->getHand()->numberOfCards(); k++) {
        currentCard = gm->getCurrentPlayer()->getHand()->getCards().at(k);
        if (gm->isLegalPlay(currentCard)) {
            legalExists = true;
            // play the first legal card
            std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " plays " << *currentCard << "." << std::endl;
            gm->getCurrentPlayer()->getHand()->removeCard(currentCard);
            gm->addCardToTable(currentCard);
            gm->updateLegalCards(currentCard);
            break;
        }
    }
    if (!legalExists) {
        // discard the first card in the player's hand
        currentCard = gm->getCurrentPlayer()->getHand()->getCards().at(0);
        std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " discards " << *currentCard << "." << std::endl;
        gm->getCurrentPlayer()->getHand()->removeCard(currentCard);
        gm->getCurrentPlayer()->discard(currentCard);
        gm->getCurrentPlayer()->awardPoints(currentCard->getRank() + 1);
    }
    gm->setNextPlayer();
}

ComputerPlayer::~ComputerPlayer() { }