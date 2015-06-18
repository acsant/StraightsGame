#include <iostream>

using namespace std;

#include "Deck.h"
#include "GameManager.h"

int main(int argc, char* argv[]) {
    GameManager* gm = GameManager::getInstace();
    if (argv[1]) {
        gm->setSeed((int) *argv[1]);
    }
    gm->createGame();
    return 0;
}