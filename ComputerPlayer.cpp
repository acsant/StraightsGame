//
// Created by Akash Sant on 15-06-18.
//

#include "ComputerPlayer.h"
#include "GameManager.h"



ComputerPlayer::ComputerPlayer() {

}

void ComputerPlayer::play(Command c) {

    GameManager* gm = GameManager::getInstance();
    bool legalExists = false;
    Card* currentCard;
    for (int k = 0; k < gm->getCurrentPlayer()->getHand()->numberOfCards(); k++) {
        currentCard = gm->getCurrentPlayer()->getHand()->getCards().at(k);
        if (gm->isLegalPlay(currentCard)) {
            legalExists = true;
            std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " plays " << *currentCard << "." << std::endl;
            gm->getCurrentPlayer()->getHand()->removeCard(currentCard);
            gm->addCardToTable(currentCard);
            gm->updateLegalCards(currentCard);
            break;
        }
    }
    if (!legalExists) {
        currentCard = gm->getCurrentPlayer()->getHand()->getCards().at(0);
        std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " discards " << *currentCard << "." << std::endl;
        gm->getCurrentPlayer()->getHand()->removeCard(currentCard);
        gm->getCurrentPlayer()->discard(currentCard);
        gm->getCurrentPlayer()->awardPoints(currentCard->getRank() + 1);
    }
    Card *temp = new Card(CLUB, SEVEN);
    if (!gm->isLegalPlay(temp)) {
        gm->addLegalPlay("7C");
        gm->addLegalPlay("7D");
        gm->addLegalPlay("7H");
    }
    delete temp;

}

ComputerPlayer::~ComputerPlayer() { }

bool ComputerPlayer::isHuman() {
    return false;
}
