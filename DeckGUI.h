//
// Created by Akash Sant on 15-07-12.
//
#include <gdkmm/pixbuf.h>
#include <vector>
#include "Card.h"
#ifndef STRAIGHTS_DECKGUI_H
#define STRAIGHTS_DECKGUI_H


class DeckGUI {
public:
    DeckGUI();
    virtual ~DeckGUI();
    Glib::RefPtr<Gdk::Pixbuf> image( Suit s, Rank r );   // Returns the image for the specified hand_card.
    Glib::RefPtr<Gdk::Pixbuf> null();                 // Returns the image to use for the placeholder.

private:
    std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   // Contains the pixel buffer images.
};
#endif

