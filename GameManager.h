//
// Created by Akash Sant on 15-06-18.
//

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <stddef.h>
#include "Deck.h"
#include "Player.h"

class GameManager {
private:
    static bool created;
    static GameManager * gm;
    static int shuffle_seed;
    const Player* current_turn;
    Deck * deck;
    std::vector<Player*> players;
    GameManager();

public:
    static GameManager * getInstace();
    void addPlayersToGame(std::vector<std::string>);
    void createGame();
    void setSeed(int);
    void dealCards();
    void startGamePlay();
    void setFirstPlayer(const Player*);

    ~GameManager();
};

#endif //STRAIGHTS_GAMEMANAGER_H
