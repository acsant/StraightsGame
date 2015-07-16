//
// Created by Akash Sant on 15-06-18.
//

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <stddef.h>
#include <map>
#include "Deck.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Player.h"
#include <gtkmm.h>
#include "Subject.h"

class GameManager: public Subject {
private:
    std::map<Suit, std::vector<Rank>*> cards_on_table;
    bool endGame;
    static bool created;
    static GameManager * gm;
    static int shuffle_seed;
    Player* current_turn;
    Deck * deck;
    std::vector<std::string> legalPlays;
    std::map<PlayerID, Player*> players;
    int currentRound;
    GameManager();

public:
    void addLegalPlay(std::string) ;
    static GameManager *getInstance();
    void addPlayersToGame(std::vector<Glib::ustring>);
    void createGame();
    void setSeed(int);
    void dealCards();
    void setFirstPlayer(Player*);
    void addCardToTable(Card*);
    void sortCardsOnTable();
    Player* getCurrentPlayer() const ;
    std::map<Suit, std::vector<Rank>*> getCardsOnTable() const;
    std::string indexToRank(int) const;
    std::string indexToSuit(int) const;
    bool isLegalPlay(Card* c);
    void updateLegalCards(Card*);
    int getCurrentRound() const;
    void nextRound();
    bool getEndGame() const;
    void setEndGame();
    void setNextPlayer();
    std::map<PlayerID, Player*> getPlayers() const;
    void resetRound();
    ~GameManager();
};

#endif //STRAIGHTS_GAMEMANAGER_H