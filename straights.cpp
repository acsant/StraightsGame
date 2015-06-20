#include <iostream>

using namespace std;

#include "GameManager.h"
#include "Command.h"

int main(int argc, char* argv[]) {
    vector<string> player_types;
    GameManager* gm = GameManager::getInstance();
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

    while (!gm->getEndGame()) {
        gm->dealCards();
        std::cout << "A new round begins. It's player " << gm->getCurrentPlayer()->getPlayerId() << "'s turn to play." << std::endl;
        gm->getCurrentPlayer()->getStrategy()->play();
        gm->addLegalPlay("7C");
        gm->addLegalPlay("7D");
        gm->addLegalPlay("7H");
        for (int i = 0; i < 51; i++) {
            gm->getCurrentPlayer()->getStrategy()->play();
            gm->setNextPlayer();
        }
        std::map<PlayerID, Player*> playerList = gm->getPlayers();
        int lowestScore = playerList[0]->getRoundScores().at(gm->getCurrentRound());
        for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
            std::cout << "Player " << it->first << "'s discards: ";
            std::vector<Card*> playerDiscards = it->second->getDiscards();
            for (int i = 0; i < playerDiscards.size(); i++) {
                std::cout << playerDiscards[i] << " ";
            }
            std::cout << std::endl;
            std::vector<int> roundScore = it->second->getRoundScores();
            int totalScore = it->second->getGameScore() + roundScore[gm->getCurrentRound()];
            if (roundScore[gm->getCurrentRound()] < lowestScore) {
                lowestScore = roundScore[gm->getCurrentRound()];
            }
            std::cout << "Player " << it->first << "'s score: " << it->second->getGameScore() << " + " <<
                    roundScore[gm->getCurrentRound()] << " = " << totalScore << std::endl;
            if (roundScore[gm->getCurrentRound()] >= 80) {
                gm->setEndGame();
            }
        }
        if (gm->getEndGame()) {
            for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
                if (it->second->getRoundScores().at(gm->getCurrentRound()) == lowestScore) {
                    std::cout << "Player " << it->first << " wins!" << std::endl;
                }
            }
            break;
        }
        gm->nextRound();
    }

    return 0;
}


