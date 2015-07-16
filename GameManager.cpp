//
// Created by Akash Sant on 15-06-18.
//

#include "GameManager.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "algorithm"
#include "MemCheck.h"

int GameManager::shuffle_seed = 0;
bool GameManager::created = false;
GameManager * GameManager::gm = NULL;

GameManager* GameManager::getInstance() {
    MEM_ON();
    if (!created) {
        gm = new GameManager();
        created = true;
        return gm;
    } else {
        return gm;
    }
    MEM_OFF();
}
GameManager::GameManager() {
    MEM_ON();
    for (int i = 0; i < SUIT_COUNT; i++) {
        cards_on_table.insert(std::pair<Suit, std::vector<Rank>* >(Suit(i), new std::vector<Rank>()));
    }
    legalPlays = std::vector<std::string>();
    legalPlays.push_back("7S");
    endGame = false;
    currentRound = 1;
    MEM_OFF();
}

GameManager::~GameManager() {
    MEM_ON();
    created = false;
    //current_turn = NULL;
    //delete current_turn;
    for (std::map<Suit, std::vector<Rank>*>::iterator it = cards_on_table.begin(); it != cards_on_table.end(); it++) {
        delete it->second;
    }
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        //players.erase(it);
        delete it->second;
    }

    delete deck;
    MEM_OFF();
}

void GameManager::createGame() {
    MEM_ON();
    deck = Deck::getInstance();
    deck->setSeed(shuffle_seed);
    deck->shuffle();
    dealCards();
    MEM_OFF();
}

void GameManager::setSeed(int seed_) {
    shuffle_seed = seed_;
}

void GameManager::addPlayersToGame(std::vector<Glib::ustring> type) {
    MEM_ON();
    for (int i = 0; i < type.size(); i++) {
        PlayerID id;
        Player* player;
        if (type[i] == "Computer") {
            PlayerStrategy* compuStrat = new ComputerPlayer;
            player = new Player(id, compuStrat);
        } else {
            PlayerStrategy* humanStrat = new HumanPlayer;
            player = new Player(id, humanStrat);
        }
        players.insert(std::pair<PlayerID, Player*>(id, player));
    }
    MEM_OFF();
}

void GameManager::dealCards() {
    MEM_ON();
    int num_cards = 13;
    std::vector<Card*> deck_of_cards = deck->getCards();
    int i = 0;
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        for (int j = 0; j < num_cards; j++) {
            it->second->addCards(deck_of_cards[i*num_cards + j]);
        }
        i++;
    }
    MEM_OFF();
}

void GameManager::setFirstPlayer(Player* firstP) {
    MEM_ON();
    current_turn = firstP;
    MEM_OFF();
}

void GameManager::addCardToTable(Card *card) {
    MEM_ON();
    (cards_on_table.find(card->getSuit()))->second->push_back(card->getRank());
    MEM_OFF();
}

void GameManager::sortCardsOnTable() {
    MEM_ON();
    for (std::map<Suit, std::vector<Rank>* >::iterator it = cards_on_table.begin(); it != cards_on_table.end(); it++) {
        std::sort(it->second->begin(), it->second->end());
    }
    MEM_OFF();
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
    std::ostringstream ss;
    ss << i+1;
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

Player* GameManager::getCurrentPlayer() const {
    return current_turn;
}

void GameManager::addLegalPlay(std::string play) {
    legalPlays.push_back(play);
}

bool GameManager::isLegalPlay(Card *c) {
    MEM_ON();
    std::string card = indexToRank(c->getRank()) + (indexToSuit(c->getSuit())).at(0);
    for (int i = 0; i < legalPlays.size(); i++) {
        if (legalPlays.at(i) == card) {
            return true;
        }
    }
    MEM_OFF();
    return false;
}

void GameManager::updateLegalCards(Card* c) {
    MEM_ON();
    std::string toAddLow;
    if (c->getRank() - 1 >= 0) {
        toAddLow = indexToRank(c->getRank() - 1) + indexToSuit(c->getSuit()).at(0);
        Card*lowCheck = new Card(Suit(c->getSuit()), Rank(c->getRank() - 1));
        if (!isLegalPlay(lowCheck)) {
            legalPlays.push_back(toAddLow);
        }
        delete lowCheck;
    }
    std::string toAddHigh;
    if (c->getRank() + 1 < 13) {
        toAddHigh = indexToRank(c->getRank() + 1) + indexToSuit(c->getSuit()).at(0);
        Card* highCheck = new Card(Suit(c->getSuit()), Rank(c->getRank() + 1));
        if (!isLegalPlay(highCheck)) {
            legalPlays.push_back(toAddHigh);
        }
        delete highCheck;
    }
    MEM_OFF();

}

int GameManager::getCurrentRound() const {
    return currentRound;
}

void GameManager::nextRound() {
    currentRound++;
}

bool GameManager::getEndGame() const {
    return endGame;
}

std::map<PlayerID, Player *> GameManager::getPlayers() const {
    return players;
}

void GameManager::setEndGame() {
    endGame  = true;
}

void GameManager::setNextPlayer() {
    MEM_ON();
    int temp_id = current_turn->getPlayerId().player_id;
    PlayerID next_id ((temp_id % 4) + 1);
    current_turn = players[next_id];
    MEM_OFF();
}

void GameManager::resetRound() {
    //delete deck;
    MEM_ON();
    endGame = false;
    legalPlays.clear();
    legalPlays.push_back("7S");
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        it->second->removePlaysFirst();
        it->second->addRound();
        it->second->resetPlayer();
    }
    MEM_OFF();
    //createGame();
}