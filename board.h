#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include <vector>

// Define the piece structure
struct Piece {
    char type;           // Type of the piece (e.g., 'P', 'N', 'B', etc.)
    PlayerColor color;   // Color of the piece (WHITE or BLACK)
    bool hasMoved = false;

    Piece(char t = '.', PlayerColor c = PlayerColor::WHITE) : type(t), color(c) {}  // Default constructor
};

// Define the chessboard structure
class ChessBoard {
private:
   
    

public:
    std::vector<std::pair<Piece, std::pair<int, int> > > whitePieces;
    std::vector<std::pair<Piece, std::pair<int, int> > > blackPieces;

    Piece board[BOARD_SIZE][BOARD_SIZE];  // 8x8 chessboard
    
    ChessBoard();

    void initializeBoard();
    void displayBoard() const;

    bool makeMove(const std::string& move, PlayerColor color);

    bool isValidMove(const std::string& move) const;

    bool isValidMoveWithoutCheck(const std::string& move) const;

    std::vector<std::string> getPossibleMoves(PlayerColor color) const;

    const std::vector<std::pair<Piece, std::pair<int, int> > >& getPieces(PlayerColor color) const;

    bool isEmpty(int row, int col) const;

    bool isWhitePieceAt(int row, int col) const;

    bool isInBounds(int row, int col) const ;
  
    bool isKingInCheck(PlayerColor color) const;

    void fromFEN(const std::string& fen);
    std::string toFEN() const;

};

#endif // BOARD_H
