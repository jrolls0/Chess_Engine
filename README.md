#C++ Chess Engine 

##Description
Welcome to the C++ Chess Simulator repository! This program allows you to play chess against a computer AI opponent right in your terminal. Designed with simplicity and functionality in mind, this is a great tool for practicing chess or simply enjoying the game. The opponent AI has an Elo rating of around 400, making it a good starting point for beginners.

##Prerequisites
A machine with C++ compiler (GCC is recommended)
Terminal to run the command-line interface

##Installation
Clone the repository to your local machine:
        git clone https://github.com/[Your_GitHub_Username]/ChessSimulator.git

Navigate to the directory where you've cloned the repo:
        cd ChessSimulator

Compile the source files:
        g++ main.cpp AIPlayer.cpp board.cpp -o chess

Run the game:
        ./chess

##Usage
Once the game is running, you'll see the chess board displayed in your terminal. The game follows standard chess rules.
To make a move, use the following format [initial square][destination square]. For example, to move a pawn from e2 to e4, type e2e4.
The board will update, and the AI will make its move.

##Acknowledgments
Jeremy Rolls
