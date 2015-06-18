//
// Created by Akash Sant on 15-06-18.
//

#include "GameManager.h"

bool GameManager::created = false;
GameManager * GameManager::gm = NULL;

GameManager* GameManager::getInstace() {
    if (!created) {
        gm = new GameManager();
        created = true;
        return gm;
    } else {
        return gm;
    }
}
GameManager::GameManager() { }
GameManager::~GameManager() {
    created = false;
}

