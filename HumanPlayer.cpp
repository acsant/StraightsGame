//
// Created by Akash Sant on 15-06-18.
//

#include "HumanPlayer.h"
#include "GameManager.h"

HumanPlayer::HumanPlayer() {

}


HumanPlayer::~HumanPlayer() {
}

void HumanPlayer::play() {
    GameManager* gm = GameManager::getInstance();
    gm->sortCardsOnTable();
    std::map<Suit, std::vector<Rank>*> played_cards = gm->getCardsOnTable();
    std::cout << "Cards on the table:" << std::endl;
    std::string tempString;
    for (std::map<Suit, std::vector<Rank>* >::iterator it = played_cards.begin(); it != played_cards.end(); it++) {
        tempString = gm->indexToSuit(it->first);
        std::cout << tempString << ": " ;
        for (std::vector<Rank>::iterator it2 = it->second->begin(); it2 != it->second->end(); it2++) {
            tempString = gm->indexToRank(*it2);
            std::cout << tempString << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Your hand: " << *(gm->getCurrentPlayer()->getHand()) << std::endl;
    std::cout << "Legal plays: ";
    for (int i = 0; i < gm->getLegalPlays()->size(); i++) {
        std::cout << gm->getLegalPlays()->at(i) << " ";
    }
    std::cout << std::endl;
    Command c;
    while (!(std::cin.eof())) {
        std::cin >> c;
        if (c.type == PLAY) {
            if (gm->isLegalPlay(&c.card)) {
                std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " plays " << c.card << "." << std::endl;
                gm->getCurrentPlayer()->getHand()->removeCard(&c.card);
                gm->addCardToTable(&c.card);
                gm->updateLegalCards(&c.card);
                break;
            } else {
                std::cout << "This is not a legal play." << std::endl;
            }
        } else if (c.type == DISCARD) {
            bool legalExists = false;
            for (int k = 0; k < gm->getCurrentPlayer()->getHand()->numberOfCards(); k++) {
                if (gm->isLegalPlay(gm->getCurrentPlayer()->getHand()->getCards().at(k))) {
                    legalExists = true;
                    std::cout << "You have a legal play. You may not discard." << std::endl;
                    break;
                }
            }
            if (!legalExists) {
                std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " discards " << c.card << "." << std::endl;
                gm->getCurrentPlayer()->getHand()->removeCard(&c.card);
                gm->getCurrentPlayer()->discard(&c.card);
                break;
            }

        } else if (c.type == DECK) {
            std::cout << Deck::getInstance() << std::endl;
        } else if (c.type == QUIT) {
            exit(EXIT_SUCCESS);
        }
    }

}