//
// Created by Akash Sant on 15-06-18.
//

#include "HumanPlayer.h"
#include "GameManager.h"


HumanPlayer::HumanPlayer() {

}


HumanPlayer::~HumanPlayer() {
}

void HumanPlayer::play(Command c) {

    GameManager* gm = GameManager::getInstance();
    gm->sortCardsOnTable();
    std::map<Suit, std::vector<Rank>*> played_cards = gm->getCardsOnTable();
    std::cout << "Cards on the table:" << std::endl;
    std::string tempString;
    for (std::map<Suit, std::vector<Rank>* >::iterator it = played_cards.begin(); it != played_cards.end(); it++) {
        tempString = gm->indexToSuit(it->first);
        std::cout << tempString << ":" ;
        for (std::vector<Rank>::iterator it2 = it->second->begin(); it2 != it->second->end(); it2++) {
            tempString = gm->indexToRank(*it2);
            std::cout << " " << tempString;
        }
        std::cout << std::endl;
    }
    std::cout << "Your hand:" << *(gm->getCurrentPlayer()->getHand()) << std::endl;
    std::cout << "Legal plays:";
    for (int i = 0; i < gm->getCurrentPlayer()->getHand()->numberOfCards(); i++) {
        if (gm->isLegalPlay(gm->getCurrentPlayer()->getHand()->getCards().at(i))) {
            std::cout << " " << *(gm->getCurrentPlayer()->getHand()->getCards().at(i));
        }
    }
    std::cout << std::endl;
    if (c.type == PLAY) {
        if (gm->isLegalPlay(&c.card)) {
            std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " plays " << c.card << "." << std::endl;
            Card* h = gm->getCurrentPlayer()->getHand()->findCard(c.card);
            gm->getCurrentPlayer()->getHand()->removeCard(&c.card);
            gm->addCardToTable(h);
            gm->updateLegalCards(h);
        } else {
            std::cout << "This is not a legal play." << std::endl;
        }
    } else if (c.type == DISCARD) {
        std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " discards " << c.card << "." << std::endl;
        Card* h = gm->getCurrentPlayer()->getHand()->findCard(c.card);
        gm->getCurrentPlayer()->getHand()->removeCard(h);
        gm->getCurrentPlayer()->discard(h);
        std::cerr << c.card << "\n";
        gm->getCurrentPlayer()->awardPoints(c.card.getRank() + 1);
    } else if (c.type == RAGEQUIT) {
        gm->getCurrentPlayer()->reassessStrategy();
        std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " ragequits. A computer will now take over." << std::endl;
    }
    /*
    while (!(std::cin.eof())) {
        std::cout << ">";
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
                gm->getCurrentPlayer()->awardPoints(c.card.getRank() + 1);
                break;
            }

        } else if (c.type == DECK) {
            std::cout << Deck::getInstance() << std::endl;
            break;
        } else if (c.type == QUIT) {
            delete gm;
            exit(EXIT_SUCCESS);
        } else if (c.type == RAGEQUIT) {
            gm->getCurrentPlayer()->reassessStrategy();
            std::cout << "Player " << gm->getCurrentPlayer()->getPlayerId() << " ragequits. A computer will now take over." << std::endl;
            break;
        }
    }
    std::cout << ">";
     */

    Card *temp = new Card(CLUB, SEVEN);
    if (!gm->isLegalPlay(temp)) {
        gm->addLegalPlay("7C");
        gm->addLegalPlay("7D");
        gm->addLegalPlay("7H");
    }
    temp = NULL;
    delete temp;

}

bool HumanPlayer::isHuman() {
    return true;
}
