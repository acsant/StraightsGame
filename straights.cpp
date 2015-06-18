#include <iostream>

using namespace std;

#include "GameManager.h"

int main(int argc, char* argv[]) {
    vector<string> player_types;
    GameManager* gm = GameManager::getInstace();
    if (argv[1]) {
        gm->setSeed((int) *argv[1]);
    }
    gm->createGame();
    for (int i = 0; i < 4; i++) {
        string temp_type;
        cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl;
        cin >> temp_type;
        player_types.push_back(temp_type);
    }
    gm->addPlayersToGame(player_types);
    gm->dealCards();
    gm->startGamePlay();
    return 0;
}