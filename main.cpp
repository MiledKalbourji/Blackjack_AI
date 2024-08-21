#include <iostream>
#include "blackjack.h"

int main() {
	Deck deck; //Create a Deck object
	deck.shuffle(); // shuffle the deck 

// Deal and display a few cards to test 
for (int i =  0; i < 5; i++) { 
       try { 
       Card card = deck.dealCard(); //Deal a card from the deck 
	std::cout << "Dealt card value: " << card.getValue() << std::endl;
       } catch (const std::out_of_range& e) {
	std::cerr << e.what() << std::endl; 
	break;
       } 
 } 
	return 0; 
} 
	
