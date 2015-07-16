//
// Created by Akash Sant on 15-07-15.
//

#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "GameManager.h"
#include <gtkmm.h>
#include <string>

class Controller {
public:
    Controller(GameManager*);
    void newGameButtonClicked(std::vector<Glib::ustring>);
    void setSeed(int seed);
    void play_card(int);
private:
    GameManager *gm_;
};


#endif //STRAIGHTS_CONTROLLER_H
