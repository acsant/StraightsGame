//
// Created by Akash Sant on 15-06-18.
//

#include "GameManager.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

int GameManager::shuffle_seed = 0;
bool GameManager::created = false;
GameManager * GameManager::gm = NULL;

GameManager* GameManager::getInstance() {
    if (!created) {
        gm = new GameManager();
        created = true;
        return gm;
    } else {
        return gm;
    }
}
GameManager::GameManager() {
    for (int i = 0; i < SUIT_COUNT; i++) {
        cards_on_table.insert(std::pair<Suit, std::vector<Rank>* >(Suit(i), new std::vector<Rank>()));
    }
}
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
            PlayerStrategy* compuStrat = new ComputerPlayer();
            player = new Player(id, compuStrat);
        } else {
            PlayerStrategy* humanStrat = new HumanPlayer();
            player = new Player(id, humanStrat);
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
    current_turn->getStrategy()->play();
}

void GameManager::addCardToTable(Card *card) {
    (cards_on_table.find(card->getSuit()))->second->push_back(card->getRank());
}

void GameManager::sortCardsOnTable() {
    for (std::map<Suit, std::vector<Rank>* >::iterator it = cards_on_table.begin(); it != cards_on_table.end(); it++) {
        std::sort(it->second->begin(), it->second->end());
    }
}

std::map<Suit, std::vector<Rank> *> GameManager::getCardsOnTable() const {
    return cards_on_table;
}

std::string GameManager::indexToSuit (int i) const {
    switch (i) {
        case 0:
            return  "Clubs";
        case 1:
            return  "Diamonds";
        case 2:
            return  "Hearts";
        case 3:
            return  "Spades";
        default:
            return  "";
    }
}

std::string GameManager::indexToRank (int i) const {
    std::istringstream ss (i + 1);
    switch (i) {
        case 0:
            return  "A";
        case 10:
            return  "J";
        case 11:
            return  "Q";
        case 12:
            return  "K";
        default:
            return  ss.str();
    }
}