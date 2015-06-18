//
// Created by Akash Sant on 15-06-18.
//

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <stddef.h>

class GameManager {
private:
    static bool created;
    static GameManager * gm;
    GameManager();

public:
    static GameManager * getInstace();
    ~GameManager();
};

#endif //STRAIGHTS_GAMEMANAGER_H
