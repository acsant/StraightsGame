//
// Created by Akash Sant on 15-07-15.
//

#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "GameManager.h"

class Controller {
public:
    Controller(GameManager*);
    void newGameButtonClicked();
private:
    GameManager *gm_;
};


#endif //STRAIGHTS_CONTROLLER_H
