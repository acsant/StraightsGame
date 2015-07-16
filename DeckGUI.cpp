//
// Created by Akash Sant on 15-07-12.
//

#include "DeckGUI.h"

using std::transform;

const char* image_names[] = {
// Set up NINE of {DIAMOND,CLUB,HEART,SPADE}
"Resources/Images/0_0.png", "Resources/Images/0_1.png", "Resources/Images/0_2.png", "Resources/Images/0_3.png",
"Resources/Images/0_4.png", "Resources/Images/0_5.png", "Resources/Images/0_6.png", "Resources/Images/0_7.png",
"Resources/Images/0_8.png", "Resources/Images/0_9.png", "Resources/Images/0_j.png", "Resources/Images/0_k.png",
"Resources/Images/0_q.png", "Resources/Images/1_0.png", "Resources/Images/1_1.png", "Resources/Images/1_2.png",
"Resources/Images/1_3.png", "Resources/Images/1_4.png", "Resources/Images/1_5.png", "Resources/Images/1_6.png",
"Resources/Images/1_7.png", "Resources/Images/1_8.png", "Resources/Images/1_9.png", "Resources/Images/1_j.png",
"Resources/Images/1_k.png", "Resources/Images/1_q.png", "Resources/Images/2_0.png", "Resources/Images/2_1.png",
"Resources/Images/2_2.png", "Resources/Images/2_3.png", "Resources/Images/2_4.png", "Resources/Images/2_5.png",
"Resources/Images/2_6.png", "Resources/Images/2_7.png", "Resources/Images/2_8.png", "Resources/Images/2_9.png",
"Resources/Images/2_j.png", "Resources/Images/2_k.png", "Resources/Images/2_q.png", "Resources/Images/3_0.png",
"Resources/Images/3_1.png", "Resources/Images/3_2.png", "Resources/Images/3_3.png", "Resources/Images/3_4.png",
"Resources/Images/3_5.png", "Resources/Images/3_6.png", "Resources/Images/3_7.png", "Resources/Images/3_8.png",
"Resources/Images/3_9.png", "Resources/Images/3_j.png", "Resources/Images/3_k.png", "Resources/Images/3_q.png",
"Resources/Images/nothing.png"
};

Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const std::string & name) {
    return Gdk::Pixbuf::create_from_file( "/Users/Akash-Mac/Documents/CS247/Straights/" + name );
}

DeckGUI::DeckGUI() {
    transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)],
        std::back_inserter(deck), &createPixbuf );
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::image( Suit s, Rank r ) {
    int index = ((int) s)*13 + ((int) r );
    return deck[ index ];
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::null() {
    int size = deck.size();
    return deck[ size-1 ];
}

DeckGUI::~DeckGUI(){}