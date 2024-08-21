// src //blackjack.h

#ifndef BLACKJACK_H     // Include guard to prvent mutliple inclusions of this header file  
#define BLACKJACK_H  // Define the BLACKJACK_H marco to signal that this file has been included 

#include <vector>
#include <random>


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
#endif //BLACKJACK_H
