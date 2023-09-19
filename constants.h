#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define the size of the chessboard
const int BOARD_SIZE = 8;

// Define piece values
const int PAWN_VALUE = 1;
const int KNIGHT_VALUE = 3;
const int BISHOP_VALUE = 3;
const int ROOK_VALUE = 5;
const int QUEEN_VALUE = 9;
const int KING_VALUE = 1000; 

// Define piece characters for both colors
const char WHITE_PAWN = 'P';
const char WHITE_KNIGHT = 'N';
const char WHITE_BISHOP = 'B';
const char WHITE_ROOK = 'R';
const char WHITE_QUEEN = 'Q';
const char WHITE_KING = 'K';

const char BLACK_PAWN = 'p';
const char BLACK_KNIGHT = 'n';
const char BLACK_BISHOP = 'b';
const char BLACK_ROOK = 'r';
const char BLACK_QUEEN = 'q';
const char BLACK_KING = 'k';

// Define player colors
enum PlayerColor {
    WHITE,
    BLACK
};

#endif // CONSTANTS_H