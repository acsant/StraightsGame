//
// Created by Akash Sant on 15-07-13.
//

#ifndef STRAIGHTS_TABLEGUI_H
#define STRAIGHTS_TABLEGUI_H
#include<gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/table.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>
#include "DeckGUI.h"
#include "Card.h"
#include <iostream>
#include <string>
#include "GameManager.h"
#include "Controller.h"

class TableGUI: public Gtk::Window, public Observer {
public:
    TableGUI(Controller*, GameManager*);
    void player_buttonAction(int);
    void updateCards(std::string player, int active_player, Hand* currentHand);
    void play_card(int);
    void start_new_game();
    void rageQuit();
    void change_seed();
    void update();
    void check_round_end();
    void resetGUI();
    void resetGame();
    void createDialog(std::string, std::string);
    void quitGame();
    virtual ~TableGUI();
private:
    Controller* controller;
    GameManager* gm_;
    bool round_update;
    DeckGUI deck;
    Gtk::VBox main_panel;
    Gtk::Frame *player_frame[4];
    Gtk::VBox *player_info[3];
    Gtk::HBox players_panel;
    Gtk::Image *hand_card[13];
    Gtk::Button *hand_button[13];
    Gtk::Button *rage_quit[4];
    Gtk::HBox hand_hbox;
    Gtk::Frame your_hand_frame;
    Gtk::Label *player_score_label[4];
    Gtk::Frame all_cards;
    Gtk::Image *table_card[52];
    Gtk::HBox *table_row[4];
    Gtk::VBox table_cards;
    Gtk::Label *discard_label[4];
    Gtk::Table main_table;
    Gtk::HBox newGameBox;
    Gtk::Button newGameButton;
    Gtk::Button changeSeedButton;
    Gtk::Button endGameButton;
    int newseed;


};


#endif //STRAIGHTS_TABLEGUI_H
