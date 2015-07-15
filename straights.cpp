#include <gtkmm.h>
#include <iostream>
#include "TableGUI.h"
using namespace std;
#include "GameManager.h"
#include "Command.h"
#include "MemCheck.h"
#include "DeckGUI.h"
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
    MEM_ON();
    Gtk::Main kit( argc, argv);
    TableGUI window;
    Gtk::Main::run(window);
    vector<string> player_types;
    GameManager* gm = GameManager::getInstance();
    if (argv[1]) {
        gm->setSeed((int) *(argv[1] - '0'));
    }
    for (int i = 0; i < 4; i++) {
        string temp_type;
        cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl;
        std::cout << ">";
        cin >> temp_type;
        player_types.push_back(temp_type);
    }
    gm->addPlayersToGame(player_types);

    while (!gm->getEndGame()) {
        gm->createGame();
        std::cout << "A new round begins. It's player " << gm->getCurrentPlayer()->getPlayerId() << "'s turn to play." << std::endl;
        gm->getCurrentPlayer()->getStrategy()->play();
        gm->addLegalPlay("7C");
        gm->addLegalPlay("7D");
        gm->addLegalPlay("7H");
        Card* c = new Card(SPADE, SEVEN);
        gm->updateLegalCards(c);
        delete c;
        for (int i = 0; i < 51; i++) {
            gm->getCurrentPlayer()->getStrategy()->play();
        }
        std::map<PlayerID, Player*> playerList = gm->getPlayers();
        Player* temp_player = playerList[1];
        int lowestScore = temp_player->getRoundScores().at(gm->getCurrentRound() - 1) + temp_player->getGameScore();
        for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
            std::cout << "Player " << it->first << "'s discards:";
            std::vector<Card*> playerDiscards = it->second->getDiscards();
            for (std::vector<Card*>::iterator it = playerDiscards.begin(); it != playerDiscards.end(); it++) {
                std::cout << " " << *(*it);
            }
            std::cout << std::endl;
            std::vector<int> roundScore = it->second->getRoundScores();
            int totalScore = it->second->getGameScore() + roundScore[gm->getCurrentRound() - 1];
            if (totalScore < lowestScore) {
                lowestScore = totalScore;
            }
            std::cout << "Player " << it->first << "'s score: " << it->second->getGameScore() << " + " <<
            roundScore[gm->getCurrentRound() - 1] << " = " << totalScore << std::endl;
            it->second->setGameScore(totalScore);
            if (totalScore >= 80) {
                gm->setEndGame();
            }
        }
        if (gm->getEndGame()) {
            for (std::map<PlayerID, Player*>::iterator it = playerList.begin(); it != playerList.end(); it++) {
                if (it->second->getGameScore() == lowestScore) {
                    std::cout << "Player " << it->first << " wins!" << std::endl;
                }
            }
            break;
        }
        gm->nextRound();
        gm->resetRound();

    }
    delete gm;
    MEM_OFF();
    return 0;
}


