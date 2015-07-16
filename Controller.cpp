//
// Created by Akash Sant on 15-07-15.
//

#include "Controller.h"
#include "GameManager.h"

Controller::Controller(GameManager* gm): gm_(gm) { }

void Controller::newGameButtonClicked(std::vector<Glib::ustring> player_types) {
    gm_->addPlayersToGame(player_types);
}

void Controller::setSeed(std::string seed) {
    int seed_ = std::stoi(seed);
    gm_->setSeed(seed_);
}
