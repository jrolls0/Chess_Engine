#include "board.h"
#include "constants.h"
#include "AIPlayer.h"
#include <iostream>
#include <string>

// extern "C" {
//     const char* getBestMove(const char* fen) {
//         ChessBoard board;
//         board.fromFEN(fen);
//         static std::string move;  // static to ensure string remains valid after return
//         move = AIPlayer::bestMove(board);
//         return move.c_str();
//     }
// }

int main() {
    ChessBoard chessboard;
    AIPlayer bot(PlayerColor::BLACK);
    std::string userMove;

    while (true) {
        // Display the current state of the board
        chessboard.displayBoard();

        // Ask the user for a move
        std::cout << "Enter your move (e.g., e2e4): ";
        std::cin >> userMove;

        // Check if the move is valid
        if (chessboard.isValidMove(userMove)) {
            chessboard.makeMove(userMove, PlayerColor::WHITE);
            std::string cunt = bot.getMove(chessboard, userMove);
            // For simplicity, we're not letting the AI make a move in this iteration
        } else {
            std::cout << "ERROR: Invalid Move" << std::endl;
        }
    }

    return 0;
}
