//
// Created by Akash Sant on 15-07-13.
//

#ifndef STRAIGHTS_TABLEGUI_H
#define STRAIGHTS_TABLEGUI_H
#include <gtkmm/window.h>
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

class TableGUI: public Gtk::Window {
public:
    TableGUI();
    virtual ~TableGUI();
private:
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
    std::vector<int> player_score;
    std::vector<int> player_discards;
    Gtk::Label *player_score_label[4];
    Gtk::Frame all_cards;
    Gtk::Image *table_card[52];
    Gtk::HBox *table_row[4];
    Gtk::VBox table_cards;
    Gtk::Label *discard_label[4];
    Gtk::Table main_table;
    Gtk::HBox newGameBox;
    Gtk::Button newGameButton;
    Gtk::Button endGameButton;

    void player_buttonAction(int);
    void start_new_game();

};


#endif //STRAIGHTS_TABLEGUI_H
