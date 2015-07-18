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
        c = Command(PLAY, card);
    } else {
        c = Command(DISCARD, card);
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
    std::string history;
    std::map<PlayerID, Player*> playerList = gm_->getPlayers();
    Player* temp_player = playerList[1];
    int lowestScore = temp_player->getRoundScores().at(gm_->getCurrentRound() - 1) + temp_player->getGameScore();
    for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
        std::stringstream ss;
        ss.str("");
        ss << it->first;
        history += "Player " + ss.str() + "'s discards:";
        std::vector<Card*> playerDiscards = it->second->getDiscards();
        for (int i = 0; i < playerDiscards.size(); i++) {
            history += " " + playerDiscards[i]->print();
        }
        history += "\n";
        std::vector<int> roundScore = it->second->getRoundScores();
        int totalScore = it->second->getGameScore() + roundScore[gm_->getCurrentRound() - 1];
        if (totalScore < lowestScore) {
            lowestScore = totalScore;
        }
        ss.str("");
        ss << it->first;
        std::string roundScr = ss.str();
        ss.str("");
        ss << it->second->getGameScore();
        std::string gameScr = ss.str();
        ss.str("");
        ss << roundScore[gm_->getCurrentRound() - 1];
        std::string scr = ss.str();
        ss.str("");
        ss << totalScore;
        std::string totScore = ss.str();
        history += "Player " + roundScr + "'s score: " + gameScr + " + " + scr + " = " + totScore + "\n";
        it->second->setGameScore(totalScore);
        gm_->setGameHistory(history);
        if (totalScore >= 80) {
            gm_->setEndGame(true);
        }
    }
    std::cout << history;
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

void Controller::resetModel() {
    gm_->resetModel();
}

void Controller::resetTableCards() {
    gm_->resetTableCards();
}

void Controller::gameStarted(bool b) {
    gm_->setGameStarted(b);

}

void Controller::resetWinnerNotification() {
    gm_->setWinnerNotification("");
}

void Controller::resetDeck() {
    gm_->resetDeck();
}

void Controller::resetHistory() {
    gm_->setGameHistory("");
}
