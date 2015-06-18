//
// Created by Akash Sant on 15-06-18.
//

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <stddef.h>
#include "Deck.h"

class GameManager {
private:
    static bool created;
    static GameManager * gm;
    static int shuffle_seed;
    Deck * deck;
    GameManager();

public:
    static GameManager * getInstace();
    void createGame();
    void setSeed(int);
    ~GameManager();
};

#endif //STRAIGHTS_GAMEMANAGER_H
