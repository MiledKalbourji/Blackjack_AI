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


// Implementation of Player methods
Player::Player() : score(0) {}

void Player::receiveCard(const Card& card) {
    hand.push_back(card);
    updateScore();
}

bool Player::wantsToHit() const {
    char choice;
    std::cout << "Your current score is " << score << ". Do you want to (h)it or (s)tand? ";
    std::cin >> choice;
    return choice == 'h' || choice == 'H';
}

int Player::getScore() const {
    return score;
}

void Player::resetHand() {
    hand.clear();
    score = 0;
}

void Player::updateScore() {
    score = 0;
    int aceCount = 0;

    for (const Card& card : hand) {
        int value = card.getValue();
        if (value == 11) { // Ace
            aceCount++;
        }
        score += value;
    }

    // Adjust score if there are aces and the score is over 21
    while (score > 21 && aceCount > 0) {
        score -= 10;
        aceCount--;
    }
}

void Player::playTurn(Deck& deck) {
    while (wantsToHit()) {
        receiveCard(deck.dealCard());
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

// Adding a reset hand method 
void Dealer::resetHand() { 
	hand.clear(); // clear the hand
	score=0; // reste the score  
} 

// Constructor for the Game class
Game::Game() {
	deck.shuffle(); // Start by shuffling the deck
}

// Play method implementation
void Game::play() {
	bool continuePlaying = true;

	while (continuePlaying) {
    	dealInitialCards(); // Deal initial cards to both player and dealer
    	player.playTurn(deck); // Handle the player's turn
    	dealer.playTurn(deck); // Handle the dealer's turn
    	determineWinner(); // Determine the winner of the game

    	// Ask the player if they want to play again
    	char choice;
    	std::cout << "Do you want to play again? (y/n): ";
    	std::cin >> choice;
    	if (choice != 'y') {
        	continuePlaying = false;
    	} else {
        	// Reset the game state if necessary
        	player.resetHand();
        	dealer.resetHand(); // reset dealer's hand properly
        	deck.shuffle(); // Shuffle the deck before the next round
    	}
	}
}

// Method to deal initial cards to both player and dealer
void Game::dealInitialCards() {
	player.receiveCard(deck.dealCard()); // Deal first card to player
	player.receiveCard(deck.dealCard()); // Deal second card to player

	dealer.addCardToHand(deck.dealCard()); // Deal first card to dealer
	dealer.addCardToHand(deck.dealCard()); // Deal second card to dealer
}

// Method to determine the winner of the game
void Game::determineWinner() {
	int playerScore = player.getScore();
	int dealerScore = dealer.getScore();

	std::cout << "Player's score: " << playerScore << "\n";
	std::cout << "Dealer's score: " << dealerScore << "\n";

	if (playerScore > 21) {
    	std::cout << "Player busts! Dealer wins.\n";
	} else if (dealerScore > 21) {
    	std::cout << "Dealer busts! Player wins.\n";
	} else if (playerScore > dealerScore) {
    	std::cout << "Player wins!\n";
	} else if (dealerScore > playerScore) {
    	std::cout << "Dealer wins!\n";
	} else {
    	std::cout << "It's a tie!\n";
	}
}
