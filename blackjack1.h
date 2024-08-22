// src //blackjack.h

#ifndef BLACKJACK_H     // Include guard to prvent mutliple inclusions of this header file  
#define BLACKJACK_H  // Define the BLACKJACK_H marco to signal that this file has been included 

#include <vector>
#include <random>
#include <iostream> //for input/output


		     // the card Class respresnts a single playing card in the game of blackjac 

class Card { 
public: 
	//Enum for the four suits in a deck of cards 
	// Hearts, Diamonds, Clubs, and Spades resprestn ths differnt suits
	enum Suit { 
		HEARTS,    // Represents the Hearts Suit
		DIAMONDS,  // Represents the Diamonds Suit
		CLUBS,     // Represents the Clubs Suit
		SPADES    // Represents the Spades Suit
	}; 
//Enum for the rank of cards starting from TWO and going up to ACE
//The values 2 to 10 correspond to their respective ranks 
//JACK,QUEEN,KING have the value of 10 in Blackjack, and ACE can be 11 or 1

	enum Rank { 
		TWO = 2, // Represents the rank '2'
		THREE, // Represents the rank '3'
		FOUR, // Represents the rank '4'
		FIVE, // Represents the rank '5'
		SIX, // Represents the rank '6'
		SEVEN, // Represents the rank '7'
		EIGHT, // Represents the rank '8'
		NINE, // Represents the rank '9'
		TEN, // Represents the rank '10'
		JACK, // Represents the rank 'Jack (Value 10 in Black Jack)'
		QUEEN, // Represents the rank 'Queen(Value 10 in Black Jack)' 
		KING, // Represents the rank 'King (Value 10 in Black Jack)'
		ACE // Represents the rank '2' (Value 11 or 1 in BlackJack)
	}; 
// Constructor that initalizes a card object with specific suit and rank 
	Card(Suit s, Rank r); 

// Method to get the value based on its rank 
// returns the appripiate value for the card ina game of Blackjack 
	int getValue() const; 
// Additional Functions can be declared here for more functionalities 
private: 
	Suit suit; // Memember variable to store the suit of the card 
	Rank rank; // Memeber variable to store the rank of the card
};

class Deck { 
public: 
	Deck(); 	// Constructor to initialize a deck of cards 
	void shuffle(); // Method to shuffle the deck 
	Card dealCard(); //Method to deal a new card from the deck
private: 
	std::vector<Card> card; // Vector to hold the deck of cards 
	std::mt19937 rng;  // Random number geraator for shuffling 
};

// Forward declarations of Player and Dealer classes 
class Player { 
public: 
	Player(); // Constructor 
	void playTurn(Deck& deck);	  //Handles the player's turn
	void addCardToHand(Card card);	 // Add a card to the player's hand
	int getScore() const; 	 //Calculate and return the player's score
private: 
	std::vector<Card> hand; //THe player's hand of cards
	int score; //the player's current score
	void updateScore(); //Update the score based on the hand
};
// Implementation of Player Methods
Player::Player() : score(0) {}

void Player::playTurn(Deck&& deck) { 
	char choice; 
	while (true) { 
		std::cout "Your score is" << getScore() << ". Do you want to (h)it or (s)tand?";
		std::cin >> choice; 
		// Handle the logic of choice hit
		if (choice == 'h') { 
			addCardToHand(deck.dealCard()); 
			updateScore(); 
			if (getScore() > 21) { //if player goes over the score of 21 
				std::cout << "You busted with a score of " << getScore () << "!\n"; //the player turn wilend 
			      	break; // end the turn if the player busts
			} 
			// Handles logic of choice stand 
		} else if (choice == 's') {  
			std::cout << "You chose to stand with a score of" << getScore() << ".\n";	
			break; //end the turn if the player stands 
		} else { 
			std::cout << "Invaild Choice please enter 'h' or 's to continue'"
		}
	} 
} 

void Player:: addCardToHand(Card card) { 
	hand.push_back(card); 
	updateScore(); 
} 

int Player::getScore() const { 
	return score; 
}
void Player::updateScore() { 
	score = 0;
	int aceCount = 0;

	for (const Card& card : hand) { 
		int value = card.getValue(); 
		if (value == 1) { //Ace
			aceCount++
	      		score += 11; //Initial value of Ace
		} else if (value > 10) { 
		       score += 10; 
		} else { 
	 		score += value; 
		} 	
} 		
			


class Dealer {  
public: 
	Dealer() ; //constructor 
	void playturn(Deck& deck); //handles the dealer's turn
	void addCardToHand(Card card); // Add a card to the dealer's hand 
	int getScore() const; // Calculate and return the dealer's score
	size_t getHandSize() const; //Return the number of cards
private:
	std::vector<Card> hand; //The dealer's hands of cards 
	int score; // The dealer's current score 
	void updateScore(); // Update the Dealer score based on hand
}; 	 	
		
class Game { 
public:
	//constructor:intializes a new game instance
	Game();

	// Method to start and manage the game loop 
	void play();

private: 
	//The deck of cards used in the game 
	Deck deck; 
	
	// the player object representing the human player
	Player player; 
	
	// The dealer object representing the dealer (AI or Automated)
	Dealer dealer;

	void dealInitialCards(); 
	void determineWinner();
};

// Implementation of Game Method
Game::Game() : deck() {} 

void Game::play() { 
	while(true) { 
		dealInitialCards(); 
		player.playTurn(); 
		dealer.playTurn(); 
		determineWinner();
	} 
} 

void Game::dealInitialCards() { 
	// Deal two cards to player and two cards to dealer
	player.addCardToHand(deck.dealCard());
        player.addCardToHand(deck.dealCard());	
	dealer.addCardToHand(deck.dealCard());
        dealer.addCardToHand(deck.dealCard());
}
void Game::determineWinner() { 
	int playerScore = player.getScore(); 
	int dealerScore = dealer.getScore(); 

	// simple Winner determination logic 
	if (playerScore > 21) { 
		// player busts 
	} else if (dealerScore > 21 || playerScore > dealerScore) {
		// Player wins 
	} else if (playerScore < dealerScore) { 
		// Dealer wins 
	} else { 
		// It's a tie 
	} 
} 
}; 
#endif //BLACKJACK_H
