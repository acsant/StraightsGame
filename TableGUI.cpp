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

    newGameButton.signal_clicked().connect( sigc::mem_fun( *this, &TableGUI::onButtonClicked ) );

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
        (*rage_quit[i-1]).signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &TableGUI::player_buttonAction), i-1));
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

void TableGUI::onNewGameButtonClicked() {
    // Create the message dialog box with stock "Ok" and "Cancel" buttons.
    Gtk::Dialog dialog( "Enter Seed Value", *this );
    
    Gtk::Entry   valueField;                  // Text entry for the user's name
    Gtk::Label   nameLabel( "Please enter the seed value:" );
    
    // Add the text entry widget to the dialog box.
    // Add the text entry widget to the vertical box section of the dialog box.
    Gtk::VBox* contentArea = dialog.get_vbox();
    contentArea->pack_start( nameLabel, true, false );
    contentArea->pack_start( nameField, true, false );
    
    nameField.set_text( "0" );
    nameLabel.show();
    nameField.show();
    
    // Add two standard buttons, "Ok" and "Cancel" with the appropriate responses when clicked.
    Gtk::Button * okButton = dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    Gtk::Button * cancelButton = dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    
    // Wait for a response from the dialog box.
    int result = dialog.run();
    std::string name;
    switch (result) {
        case Gtk::RESPONSE_OK:
        case Gtk::RESPONSE_ACCEPT:
            name = nameField.get_text();
            std::cout << "Entered '" << name << "'" << std::endl;
            break;
        case Gtk::RESPONSE_CANCEL:
            std::cout << "dialog cancelled" << std::endl;
            break;
        default:
            std::cout << "unexpected button clicked" << std::endl;
            break;
    } // switch
} // HelloWorld::onButtonClicked


void TableGUI::player_buttonAction(int button) {
    Glib::ustring label = (*rage_quit[button]).get_label();
    if (label == "Human") {
        (*rage_quit[button]).set_label("Computer");
    } else if (label == "Computer") {
        (*rage_quit[button]).set_label("Human");
    }
}
