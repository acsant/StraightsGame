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
}