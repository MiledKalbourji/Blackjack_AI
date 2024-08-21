#include "blackjack.h"    // Include the header file where the Card class is declared
#include <algorithm> // for std::shuffle
#include <ctime> //for std::time
#include <stdexcept>  // for std::out_of_range

// Constructor for the Card class
Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

// Method to get the value of the card
int Card::getValue() const {
    if (rank <= TEN) return rank;   // Cards TWO to TEN have values equal to their rank
    if (rank < ACE) return 10;      // JACK, QUEEN, and KING have a value of 10
    return 11;                      // ACE has a default value of 11
}
// Constructor to intialize the deck of cards 
Deck::Deck() :rng(std::random_device{}()) {
	// Initialize the deck with all cards 
	for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
		for(int rank = Card::TWO; rank <= Card::ACE; ++rank) { 
			card.emplace_back(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank));
		}
	}
}

// Method to shuffle the deck 
void Deck::shuffle() { 
	//use std::shuffle with a random number generator to shuffle the cards 
	std::shuffle(card.begin(), card.end(), rng); 
} 

//Method to deal a card from the deck 
Card Deck::dealCard() {
       if (card.empty()) {
		throw std::out_of_range("no cards left in the deck");
       } 
	// Take the top card of the deck 
	Card dealtCard = card.back(); 
	card.pop_back();
	return dealtCard; 
} 
	 


