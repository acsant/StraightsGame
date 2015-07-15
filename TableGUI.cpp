//
// Created by Akash Sant on 15-07-13.
//

#include "TableGUI.h"
#include <string>

TableGUI::TableGUI() : main_panel(false, 10), players_panel(false, 10), hand_hbox(false, 10), table_cards(false, 10), main_table(10,10, true) {
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.null();
    //const Glib::RefPtr<Gdk::Pixbuf> sev_spades = deck.image(SPADE, SEVEN);
    set_border_width(10);

    your_hand_frame.set_label("Your Hand: ");
    your_hand_frame.set_border_width(10);
    all_cards.set_label("Cards on the table");
    table_cards.set_border_width(10);

    // Add the your_hand_frame to the window. Windows can only hold one widget, same for frames.
    add(main_panel);
    main_panel.add(newGameBox);
    newGameBox.add(newGameButton);
    newGameBox.add(endGameButton);
    main_panel.add(all_cards);
    main_panel.add(players_panel);
    main_panel.add(your_hand_frame);
    // Add the horizontal box for laying out the images to the your_hand_frame.
    your_hand_frame.add(hand_hbox);
    all_cards.add(table_cards);

    newGameButton.set_label("New Game");
    endGameButton.set_label("End Game");

    for (int i = 0; i < 4; i++) {
        table_row[i] = new Gtk::HBox(true, 10);
        for (int j = 0; j < 13; j++) {
            table_card[(i+1)*(j+1) - 1] = new Gtk::Image( nullCardPixbuf );
            (*table_row[i]).add(*table_card[(i+1)*(j+1) - 1]);
        }
        table_cards.add(*table_row[i]);
    }
    players_panel.set_border_width(10);


    for (int i = 1; i <= 4; i++) {
        player_frame[i-1] = new Gtk::Frame();
        std::string plr = std::to_string(i);
        (*player_frame[i-1]).set_label("Player " + plr);
        players_panel.add(*player_frame[i-1]);
        //Rage quit
        player_info[i-1] = new Gtk::VBox(true, 10);
        player_info[i-1]->set_spacing(1);
        (*player_frame[i-1]).add(*player_info[i-1]);
        rage_quit[i-1] = new Gtk::Button();
        (*player_info[i-1]).add(*rage_quit[i-1]);
        (*rage_quit[i-1]).set_label("Human");
        (*rage_quit[i-1]).set_border_width(5);
        // Scores
        player_score_label[i-1] = new Gtk::Label();
        player_score.push_back(0);
        (*player_score_label[i-1]).set_label(std::to_string(player_score.at(i-1)) + " points");
        (*player_info[i-1]).add((*player_score_label[i-1]));

        //Discards
        discard_label[i-1] = new Gtk::Label();
        player_discards.push_back(0);
        (*discard_label[i-1]).set_label(std::to_string(player_discards.at(i-1)) + " discards");
        (*player_info[i-1]).add(*discard_label[i-1]);
    }

    // Initialize 4 empty cards and place them in the box.
    for (int i = 0; i < 13; i++ ) {
        hand_card[i] = new Gtk::Image( nullCardPixbuf );
        hand_button[i] = new Gtk::Button();
        hand_button[i]->set_image(*hand_card[i]);
        hand_hbox.add( *hand_button[i] );
    } // for
    hand_hbox.set_border_width(10);


    // The final step is to display this newly created widget.
    show_all();
}

TableGUI::~TableGUI() {
    for (int i = 0; i < 5; i++ ) delete hand_card[i];
}

void TableGUI::player_buttonAction() {
    if () {}
}
