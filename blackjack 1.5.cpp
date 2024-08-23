#include "blackjack.h"    // Include the header file where the Card class is declared
#include <algorithm> // for std::shuffle
#include <ctime> //for std::time
#include <stdexcept>  // for std::out_of_range
#include <iostream> //for input/output
		   
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

// Constructor implementation
Game::Game() { 
    // Initialize the game state
    deck.shuffle(); // Starts shuffling the deck
    // Initialize other game state variables here if necessary
}

// Play Method implementation 
void Game::play() { 
    while (true) {
	  // 1. Deal initial cards to player and dealer
        player.receiveCard(deck.dealCard());
        player.receiveCard(deck.dealCard());
        dealer.addCardToHand(deck.dealCard());
        dealer.addCardToHand(deck.dealCard());

        // 2. Player's turn: allow the player to hit or stand
        while (player.wantsToHit()) {
            player.receiveCard(deck.dealCard());
        }

        // 3. Dealer's turn: dealer's logic to hit or stand
        dealer.playTurn(deck);
	 // 4. Determine winner and adjust scores accordingly
        determineWinner();

        // 5. Optionally, ask the player if they want to play another round
        char choice;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> choice;
        if (choice != 'y') {
            break;  // Exit the game loop if the player doesn't want to play again
        }

        // 6. Reset the deck or shuffle if necessary
        deck.shuffle();
    }
}
// Implementation of Dealer methods 
Dealer::Dealer() : score(0){} 
void Dealer::playTurn(Deck& deck){ 
	//Dealer will keep drwing until their is 17 or higher
	while (getScore() < 17) { 
		addCardToHand(deck.dealCard()); 
		std::cout << "Dealer drew a card. Dealers score is now" <<getScore() << ".\n"; 
	} 

	if (getScore() > 21) { 
		std::cout << "Dealer Busted with a score of " << getScore() << "!\n";
	}
} 	
void Dealer::addCardToHand(Card card) { 
	hand.push_back(card);
	updateScore();
} 

int Dealer::getScore() const { 
	return score; 
} 
void Dealer::updateScore() {
	score =0; 
	int aceCount =0; 
	
	for (const Card& card : hand) { 
	     int value = card.getValue();
	    if (value == 11) { // Ace 
		aceCount++; 
	       value = 11; 
	    } else if (value > 10) { // Face Cards 
		value = 10; 
	    } 
	    score += value; 
	} 	    



	// Adjust score if there are aces and the score is over 21 
	while (score > 21 && aceCount > 0) { 
		score -= 10; 
		aceCount--; 
	} 
}
size_t Dealer::getHandSize() const {
    return hand.size();
}
