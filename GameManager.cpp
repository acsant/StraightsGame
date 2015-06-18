//
// Created by Akash Sant on 15-06-18.
//

#include "GameManager.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

int GameManager::shuffle_seed = 0;
bool GameManager::created = false;
GameManager * GameManager::gm = NULL;

GameManager* GameManager::getInstace() {
    if (!created) {
        gm = new GameManager();
        created = true;
        return gm;
    } else {
        return gm;
    }
}
GameManager::GameManager() { }
GameManager::~GameManager() {
    created = false;
}

void GameManager::createGame() {
    deck = Deck::getInstance();
    deck->setSeed(shuffle_seed);
    deck->shuffle();
}

void GameManager::setSeed(int seed_) {
    shuffle_seed = seed_;
}

void GameManager::addPlayersToGame(std::vector<std::string> type) {
    for (int i = 0; i < type.size(); i++) {
        PlayerID id;
        Player* player;
        if (type[i] == "c") {
            player = new ComputerPlayer(id);

        } else {
            player = new HumanPlayer(id);
        }
        players.push_back(player);
    }
}

void GameManager::dealCards() {
    int num_cards = 13;
    std::vector<Card*> deck_of_cards = deck->getCards();
    int check = players.size();
    for (int i = 0; i < players.size(); i++) {
        check = check;
        for (int j = 0; j < num_cards; j++) {
            players[i]->addCards(deck_of_cards[i*num_cards + j]);
        }
    }
}

void GameManager::setFirstPlayer(const Player* firstP) {
    firstToPlay = firstP;
}