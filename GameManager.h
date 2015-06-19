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

class GameManager {
private:
public:
    const std::map<Suit, std::vector<Rank> *> &getCards_on_table() const {
        return cards_on_table;
    }

private:
    std::map<Suit, std::vector<Rank>*> cards_on_table;
    static bool created;
    static GameManager * gm;
    static int shuffle_seed;
    const Player* current_turn;
    Deck * deck;
    std::map<PlayerID, Player*> players;
    GameManager();

public:
    static GameManager *getInstance();
    void addPlayersToGame(std::vector<std::string>);
    void createGame();
    void setSeed(int);
    void dealCards();
    void startGamePlay();
    void setFirstPlayer(const Player*);
    void addCardToTable(Card*);
    void sortCardsOnTable();
    std::map<Suit, std::vector<Rank>*> getCardsOnTable() const;
    std::string indexToRank(int) const;
    std::string indexToSuit(int) const;
    ~GameManager();
};

#endif //STRAIGHTS_GAMEMANAGER_H
