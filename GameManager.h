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
    Deck * deck;
    std::vector<Player*> players;
    GameManager();

public:
    static GameManager * getInstace();
    void addPlayersToGame(std::vector<std::string>);
    void createGame();
    void setSeed(int);
    void dealCards();
    ~GameManager();
};

#endif //STRAIGHTS_GAMEMANAGER_H
