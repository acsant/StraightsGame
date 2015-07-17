//
// Created by Akash Sant on 15-07-13.
//

#include "TableGUI.h"
#include <string>

TableGUI::TableGUI(Controller* c, GameManager* gm) : controller(c), gm_(gm), main_panel(false, 10), players_panel(false, 10), hand_hbox(false, 10), table_cards(false, 10), main_table(10,10, true) {
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.null();
    //const Glib::RefPtr<Gdk::Pixbuf> sev_spades = deck.image(SPADE, SEVEN);
    set_border_width(10);

    your_hand_frame.set_label("Player Hand: ");
    your_hand_frame.set_border_width(10);
    all_cards.set_label("Cards on the table");
    table_cards.set_border_width(10);

    // Add the your_hand_frame to the window. Windows can only hold one widget, same for frames.
    add(main_panel);
    main_panel.add(newGameBox);
    newGameBox.add(newGameButton);
    newGameBox.add(changeSeedButton);
    newGameBox.add(endGameButton);
    main_panel.add(all_cards);
    main_panel.add(players_panel);
    main_panel.add(your_hand_frame);
    // Add the horizontal box for laying out the images to the your_hand_frame.
    your_hand_frame.add(hand_hbox);
    all_cards.add(table_cards);

    newGameButton.set_label("New Game");
    changeSeedButton.set_label("Change Seed Value");
    endGameButton.set_label("End Game");

    for (int i = 0; i < 4; i++) {
        table_row[i] = new Gtk::HBox(true, 10);
        for (int j = 0; j < 13; j++) {
            table_card[i*13 + j] = new Gtk::Image( nullCardPixbuf );
            (*table_row[i]).add(*table_card[i*13 + j]);
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
        (*player_score_label[i-1]).set_label("0 points");
        (*player_info[i-1]).add((*player_score_label[i-1]));

        //Discards
        discard_label[i-1] = new Gtk::Label();
        (*discard_label[i-1]).set_label("0 discards");
        (*player_info[i-1]).add(*discard_label[i-1]);
    }

    // Initialize 4 empty cards and place them in the box.
    for (int i = 0; i < 13; i++ ) {
        hand_card[i] = new Gtk::Image( nullCardPixbuf );
        hand_button[i] = new Gtk::Button();
        hand_button[i]->set_image(*hand_card[i]);
        hand_hbox.add( *hand_button[i] );
        hand_button[i]->signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &TableGUI::play_card), i));
    } // for
    hand_hbox.set_border_width(10);
    gm_->subscribe(this);
    // On start of a new game
    newGameButton.signal_clicked().connect(sigc::mem_fun(*this, &TableGUI::start_new_game));

    //On updating seed value
    changeSeedButton.signal_clicked().connect(sigc::mem_fun(*this, &TableGUI::change_seed));

    // The final step is to display this newly created widget.
    show_all();
}

TableGUI::~TableGUI() {
    for (int i = 0; i < 5; i++ ) delete hand_card[i];
}

void TableGUI::player_buttonAction(int button) {
    Glib::ustring label = (*rage_quit[button]).get_label();
    if (label == "Human") {
        (*rage_quit[button]).set_label("Computer");
    } else if (label == "Computer") {
        (*rage_quit[button]).set_label("Human");
    }
}

void TableGUI::start_new_game() {

    std::vector<Glib::ustring> player_types;
    for (Gtk::Button* button : rage_quit) {
        player_types.push_back(button->get_label());
        button->set_label("Rage!");
    }
    controller->newGameButtonClicked(player_types);
    for (int i = 0; i < 4; i++) {
        (*rage_quit[i]).signal_clicked().connect(sigc::mem_fun(*this, &TableGUI::rageQuit));
    }
    Gtk::Dialog dialog( "Notification", *this, true, true);
    Glib::ustring turn_notification = "The game has started. It is Player " + std::to_string(gm_->getCurrentPlayer()->getPlayerId().player_id) + "'s turn.";
    Gtk::Label   nameLabel( turn_notification );
    Gtk::VBox* contentArea = dialog.get_vbox();
    contentArea->pack_start( nameLabel, true, false );
    Gtk::Button * okButton = dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    nameLabel.show();
    int res = dialog.run();
}

void TableGUI::change_seed() {
    Gtk::Dialog dialog( "Enter New Seed Value", *this, true, true);

    Gtk::Entry   nameField;                  // Text entry for the user's seed
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
    std::stringstream s;
    switch (result) {
        case Gtk::RESPONSE_OK:
        case Gtk::RESPONSE_ACCEPT:
            s << nameField.get_text().raw();
            s >> newseed;
            std::cout << "Entered '" << newseed << "'" << std::endl;
            controller->setSeed(newseed);
            break;
        case Gtk::RESPONSE_CANCEL:
            std::cout << "dialog cancelled" << std::endl;
            break;
        default:
            std::cout << "unexpected button clicked" << std::endl;
            break;
    } // switch
}

void TableGUI::update() {
    int active_player = gm_->getCurrentPlayer()->getPlayerId().player_id;
    Hand* currentHand;
    // Everything before next player
    Player* updated_player = gm_->getPlayers().find(active_player)->second;
    std::vector<int> roundScores = updated_player->getRoundScores();
    (*player_score_label[active_player - 1]).set_label(std::to_string(updated_player->getGameScore() + roundScores.at(roundScores.size() - 1)) + " points");
    int discard = updated_player->getDiscards().size();
    std::stringstream ss;
    ss << discard;
    (*discard_label[active_player - 1]).set_label(ss.str() + " discards");
    // Controller changes to next player
    if(!gm_->get_round_end()) {
        if (gm_->getLegalPlays().size() > 1) {
            controller->setNextPlayer();
        }
        currentHand = gm_->getCurrentPlayer()->getHand();
        active_player = gm_->getCurrentPlayer()->getPlayerId().player_id;
        std::stringstream playerStream;
        playerStream.clear();
        playerStream << active_player;
        std::string player = "";
        player = playerStream.str();
        player.erase(0, player.find_first_not_of('0'));
    //update all cards
        updateCards(player, active_player, currentHand);
    //delete currentHand;
        if(!gm_->get_round_end()) {
            check_round_end();
        }
    }
}

void TableGUI::check_round_end() {
    bool end_round = true;
    std::map<PlayerID, Player*> players = gm_->getPlayers();
    Player* currPlayer = gm_->getCurrentPlayer();
    for (std::map<PlayerID, Player*>::iterator it = players.begin(); it != players.end(); it++) {
        currPlayer = (*it).second;
        if (currPlayer->getHand()->numberOfCards() > 0) {
            end_round = false;
        }
    }
    currPlayer = NULL;
    delete currPlayer;
    if (end_round) {
        controller->resetRound();
    }
}

void TableGUI::play_card(int index) {
    std::vector<Card*> current_hand = gm_->getCurrentPlayer()->getHand()->getCards();
    if (index < gm_->getCurrentPlayer()->getHand()->numberOfCards()) {
        Card card = *current_hand.at(index);
        if (gm_->has_legal() && !gm_->isLegalPlay(&card)) {
            Gtk::Dialog dialog("ERROR", *this, true, true);
            Glib::ustring turn_notification = "This is not a legal play.";
            Gtk::Label nameLabel(turn_notification);
            Gtk::VBox *contentArea = dialog.get_vbox();
            contentArea->pack_start(nameLabel, true, false);
            Gtk::Button *okButton = dialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
            nameLabel.show();
            dialog.run();
        } else {
            controller->play_card(index);
        }
    }
}

void TableGUI::updateCards(std::string player, int active_player, Hand* currentHand){
    Glib::RefPtr<Gdk::Pixbuf> cardPixBuf;
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.null();
    std::map<Suit, std::vector<Rank> *> cards_on_table = gm_->getCardsOnTable();
    your_hand_frame.set_label("Player " + player + "'s Hand");
    // If its the current player, set all the cards and change player turn
    if (gm_->getCurrentPlayer()) {
        for (int i = 0; i < 4; i++) {
            if (i+1 != active_player) {
                rage_quit[i]->set_sensitive(false);
            } else {
                rage_quit[i]->set_sensitive(true);
            }
        }
        for (int i = 0; i < currentHand->numberOfCards(); i++) {
            Card* currentCard = currentHand->getCards().at(i);
            cardPixBuf = deck.image(currentCard->getSuit(), currentCard->getRank());
            hand_card[i]->set(cardPixBuf);
            hand_button[i]->set_sensitive(true);
            if (!gm_->isLegalPlay(currentCard)) {
                hand_card[i]->set_sensitive(false);
            } else {
                hand_card[i]->set_sensitive(true);
            }
        }
        if (currentHand->numberOfCards() < 13) {
            for (int i = 12; i >= currentHand->numberOfCards(); i--) {
                hand_card[i]->set(nullCardPixbuf);
                hand_card[i]->set_sensitive(false);
                hand_button[i]->set_sensitive(false);
            }
        }
    }
    int k = 0;
    for (std::map<Suit, std::vector<Rank> *>::iterator it = cards_on_table.begin(); it != cards_on_table.end(); it++) {
        std::vector<Rank> cards_of_rank = *(*it).second;
        for (int j = 0; j < cards_of_rank.size(); j++) {
            cardPixBuf = deck.image((*it).first, cards_of_rank[j]);
            int num = (*it).first*13 + cards_of_rank[j];
            table_card[num]->set(cardPixBuf);
        }
        k++;
    }
}

void TableGUI::rageQuit() {
    controller->rageQuit();
}
