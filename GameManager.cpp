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
    gameStart = false;
    currentRound = 1;
    round_ended = false;
    new_round = false;
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
    round_ended = false;
    new_round = true;
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
    gm->createGame();
    notify();
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

void GameManager::setEndGame(bool b) {
    endGame  = b;
}

void GameManager::setNextPlayer() {
    MEM_ON();
    int temp_id = current_turn->getPlayerId().player_id;
    PlayerID next_id ((temp_id % 4) + 1);
    current_turn = players[next_id];
    if (!current_turn->getStrategy()->isHuman() && !get_round_end() && current_turn->getHand()->numberOfCards() > 0) {
        Command c;
        current_turn->getStrategy()->play(c);
        notify();
    }
    MEM_OFF();
}

void GameManager::resetRound() {
    //delete deck;
    MEM_ON();
    legalPlays.clear();
    legalPlays.push_back("7S");
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        it->second->removePlaysFirst();
        it->second->addRound();
        it->second->resetPlayer();
    }
    MEM_OFF();
    if (!endGame) {
        createGame();
    }
}

void GameManager::play_card(Command command) {
    current_turn->getStrategy()->play(command);
    notify();
}

bool GameManager::has_legal() {
    Hand* currentHand = current_turn->getHand();
    bool has_legal = false;
    std::vector<Card*> player_cards = currentHand->getCards();
    for (std::vector<Card*>::iterator it = player_cards.begin(); it != player_cards.end(); it++) {
        if (isLegalPlay(*it)) {
            return true;
        }
    }
    return has_legal;
}

std::vector<std::string> GameManager::getLegalPlays() {
    return legalPlays;
}

void GameManager::rage_quit(Command c) {
    if (!endGame) {
        current_turn->getStrategy()->play(c);
        current_turn->getStrategy()->play(c);
        notify();
    }
}

void GameManager::set_round_end(bool ended) {
    round_ended = ended;
}

bool GameManager::get_round_end() {
    return round_ended;
}

void GameManager::checkEndGame(std::map<PlayerID, Player*> playerList, int lowestScore) {
    if (endGame) {
        for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
            if (it->second->getGameScore() == lowestScore) {
                std::cout << "Player " << it->first << " wins!" << std::endl;
                std::stringstream ss;
                ss.clear();
                ss << it->first;
                winner_notification += "Player " + ss.str() + " wins!\n";
            }
        }
        notify();
    }
}

bool GameManager::isNewRound() {
    return new_round;
}

void GameManager::setNewRound(bool b) {
    new_round = b;
}

void GameManager::resetModel() {
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        delete (*it).second;
    }
    players.clear();
    current_turn = NULL;
    legalPlays.clear();
    legalPlays.push_back("7S");
    currentRound = 0;

}

void GameManager::resetTableCards() {
    for (std::map<Suit, std::vector<Rank> *>::iterator it = cards_on_table.begin(); it != cards_on_table.end(); it++) {
        delete (*it).second;
    }
    cards_on_table.clear();
    for (int i = 0; i < SUIT_COUNT; i++) {
        cards_on_table.insert(std::pair<Suit, std::vector<Rank>* >(Suit(i), new std::vector<Rank>()));
    }
}

void GameManager::setGameStarted(bool b) {
    gameStart = b;
}

bool GameManager::getGameStarted() {
    return gameStart;
}


std::string GameManager::getWinnerNotification() {
    return winner_notification;
}

void GameManager::setWinnerNotification(std::string s) {
    winner_notification = s;
}

void GameManager::resetDeck() {
    delete deck;
}
