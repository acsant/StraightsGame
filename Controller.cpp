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
    Card& card = *current_hand.at(index);
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

void Controller::rageQuit() {
    Card* card = new Card(SPADE, SEVEN);
    Command c(RAGEQUIT, *card);
    gm_->rage_quit(c);
    delete card;
}

void Controller::resetRound() {
    gm_->set_round_end(true);
    std::map<PlayerID, Player*> playerList = gm_->getPlayers();
    Player* temp_player = playerList[1];
    int lowestScore = temp_player->getRoundScores().at(gm_->getCurrentRound() - 1) + temp_player->getGameScore();
    for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
        std::cout << "Player " << it->first << "'s discards:";
        std::vector<Card*> playerDiscards = it->second->getDiscards();
        for (int i = 0; i < playerDiscards.size(); i++) {
            std::cout << " " << *(playerDiscards[i]);
        }
        std::cout << std::endl;
        std::vector<int> roundScore = it->second->getRoundScores();
        int totalScore = it->second->getGameScore() + roundScore[gm_->getCurrentRound() - 1];
        if (totalScore < lowestScore) {
            lowestScore = totalScore;
        }
        std::cout << "Player " << it->first << "'s score: " << it->second->getGameScore() << " + " <<
        roundScore[gm_->getCurrentRound() - 1] << " = " << totalScore << std::endl;
        it->second->setGameScore(totalScore);
        if (totalScore >= 80) {
            gm_->setEndGame(true);
        }
    }
    gm_->checkEndGame(playerList, lowestScore);
    gm_->nextRound();
    gm_->resetRound();
}

void Controller::setNewRound(bool b) {
    gm_->setNewRound(b);
}

void Controller::setEndGame(bool b) {
    gm_->setEndGame(b);
}

void Controller::removePlayers() {
    gm_->deletePlayers();
}
