# Blackjack AI  

## Current game state 12-19-2024 
--> Game is running with no compile errors. 
-->Correct Key binds, meaning if users press H or S the code will capture and base the game off the decisions  

## Whats Broken 
--> curren game logic is weak, the dealer score does not get reset after playing one turn.  


## Steps to make the project work
A future patch is coming to first game logic, then implement monte-carlo method for AI aspect of the game. 


## These are future goals below for I want the game is down below 

## Overview
This project is a Blackjack game implemented in C++ with AI components. The AI makes decisions based on the cards in the player's and dealer's hands. The project demonstrates the use of Monte Carlo methods and Q-Learning algorithms for reinforcement learning.

## Features
- **Card Class**: Represents individual cards with suits and ranks.
- **Deck Class**: Manages a collection of cards, shuffling, and dealing.
- **AI Logic**: (To be implemented) The AI will make decisions on whether to hit or stand based on the game state.

## Requirements
- C++17
- CMake
- OpenCV (for GUI)

## How to Build
```bash
mkdir build
cd build
cmake ..
make
