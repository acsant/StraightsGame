//
// Created by Akash Sant on 15-07-15.
//

#include "Controller.h"
#include "GameManager.h"

Controller::Controller(GameManager* gm): gm_(gm) { }

void Controller::newGameButtonClicked(std::vector<std::string> player_types) {
    gm_->addPlayersToGame(player_types);
}
