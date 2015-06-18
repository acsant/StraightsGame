//
// Created by Akash Sant on 15-06-18.
//

#include "GameManager.h"

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

}