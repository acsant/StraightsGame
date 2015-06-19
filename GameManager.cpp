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
        players.insert(std::pair<PlayerID, Player*>(id, player));
    }
}

void GameManager::dealCards() {
    int num_cards = 13;
    std::vector<Card*> deck_of_cards = deck->getCards();
    int i = 0;
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        for (int j = 0; j < num_cards; j++) {
            it->second->addCards(deck_of_cards[i*num_cards + j]);
        }
        i++;
    }
}

void GameManager::setFirstPlayer(const Player* firstP) {
    current_turn = firstP;
}

void GameManager::startGamePlay() {
    std::cout << "A new round begins. It's player " << current_turn->getPlayerId().player_id << "'s turn to play." << std::endl;
}