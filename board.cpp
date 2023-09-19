#include "board.h"
#include "constants.h"
#include <iostream>

using namespace std;

ChessBoard::ChessBoard() {
    initializeBoard();
}

void ChessBoard::initializeBoard() {
    // Clear the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = Piece('.', PlayerColor::WHITE);
        }
    }

    // Set up pawns
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = Piece(BLACK_PAWN, PlayerColor::BLACK);
        board[6][i] = Piece(WHITE_PAWN, PlayerColor::WHITE);
    }

    PlayerColor colors[] = { PlayerColor::BLACK, PlayerColor::WHITE };
    int rows[] = { 0, 7 };

    // Set up white pieces
    char whites[] = { WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK };
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[7][i] = Piece(whites[i], PlayerColor::WHITE);
    }

    // Set up black pieces
    char blacks[] = { BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK };
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[0][i] = Piece(blacks[i], PlayerColor::BLACK);
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].type != '.') {
                if (board[i][j].color == PlayerColor::WHITE) {
                    whitePieces.push_back(std::make_pair(board[i][j], std::make_pair(i, j)));

                } else if (board[i][j].color == PlayerColor::BLACK) {
                    blackPieces.push_back(std::make_pair(board[i][j], std::make_pair(i, j)));

                }
            }
        }

    }
    
}

void ChessBoard::displayBoard() const {
    std::cout << std::endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Print the y-axis numbers
        std::cout << 8 - i << "|";

        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j].type << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "  ---------------" << std::endl;
    std::cout << "  a b c d e f g h" << std::endl;  // Print the x-axis letters again for symmetry
    std::cout << std::endl;
}

bool ChessBoard::makeMove(const std::string& move, PlayerColor color) {
    int startCol = move[0] - 'a';
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0');
    
    Piece capturedPiece = board[endRow][endCol];    

    board[startRow][startCol].hasMoved = true;

    // Handling castling
    if (color == PlayerColor::WHITE && move == "e1g1") { // King-side castling for white
        board[7][6] = board[7][4];  // Move King to g1
        board[7][5] = board[7][7];  // Move Rook to f1
        board[7][4] = Piece('.', color); // Clear King's initial position
        board[7][7] = Piece('.', color); // Clear Rook's initial position
        return true;
    } 
    else if (color == PlayerColor::WHITE && move == "e1c1") { // Queen-side castling for white
        board[7][2] = board[7][4];  // Move King to c1
        board[7][3] = board[7][0];  // Move Rook to d1
        board[7][4] = Piece('.', color); // Clear King's initial position
        board[7][0] = Piece('.', color); // Clear Rook's initial position
        return true;
    } 
    else if (color == PlayerColor::BLACK && move == "e8g8") { // King-side castling for black
        board[0][6] = board[0][4];  // Move King to g8
        board[0][5] = board[0][7];  // Move Rook to f8
        board[0][4] = Piece('.', color); // Clear King's initial position
        board[0][7] = Piece('.', color); // Clear Rook's initial position
        return true;
    } 
    else if (color == PlayerColor::BLACK && move == "e8c8") { // Queen-side castling for black
        board[0][2] = board[0][4];  // Move King to c8
        board[0][3] = board[0][0];  // Move Rook to d8
        board[0][4] = Piece('.', color); // Clear King's initial position
        board[0][0] = Piece('.', color); // Clear Rook's initial position
        return true;
    }


    bool firstFound = false;
    bool secondFound = false;
    if (color == PlayerColor::WHITE) {
        for (auto& piece : whitePieces) {
            if (piece.second.first == startRow && piece.second.second == startCol) {
                board[startRow][startCol] = Piece('.', color);  // Empty the starting square
                piece.second.first = endRow;
                piece.second.second = endCol;
                board[endRow][endCol] = piece.first;  // Move the piece to the new location
                break;
            }
        }

        // If a capture occurred, remove the captured piece from the opponent's vector
        if (capturedPiece.type != '.' && capturedPiece.color != color) {
            for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it) {
                if (it->second.first == endRow && it->second.second == endCol) {
                    blackPieces.erase(it);
                    break;
                }
            }
        }
    }
    else {
        for (auto& piece : blackPieces) {
            if (piece.second.first == startRow && piece.second.second == startCol) {
                board[startRow][startCol] = Piece('.', color);  // Empty the starting square
                piece.second.first = endRow;
                piece.second.second = endCol;
                board[endRow][endCol] = piece.first;  // Move the piece to the new location
                break;
            }
        }

        // If a capture occurred, remove the captured piece from the opponent's vector
        if (capturedPiece.type != '.' && capturedPiece.color != color) {
            for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it) {
                if (it->second.first == endRow && it->second.second == endCol) {
                    whitePieces.erase(it);
                    break;
                }
            }
        }
    }

    return true;
}

bool ChessBoard::isValidMove(const std::string& move) const {
    if (!isValidMoveWithoutCheck(move)) {
        return false;
    }

    int startCol = move[0] - 'a' ;
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0') ;
    
    Piece startPiece = board[startRow][startCol];
    Piece endPiece = board[endRow][endCol];

    // If the move is made by the king or the king is currently in check
    if (startPiece.type == (startPiece.color == PlayerColor::WHITE ? WHITE_KING : BLACK_KING) ||
        isKingInCheck(startPiece.color)) {

        ChessBoard tempBoard = *this;

        tempBoard.makeMove(move, startPiece.color); 
        

        if (tempBoard.isKingInCheck(startPiece.color)) {
            return false;  
        }

    }

    return true;
}


bool ChessBoard::isValidMoveWithoutCheck(const std::string& move) const {
    int startCol = move[0] - 'a' ;
    int startRow = 8 - (move[1] - '0');
    int endCol = move[2] - 'a';
    int endRow = 8 - (move[3] - '0') ;
    
    Piece startPiece = board[startRow][startCol];
    Piece endPiece = board[endRow][endCol];

    // Check if the starting square is empty
    if (startPiece.type == '.') {
        return false;
    }

    // Check if the ending square has a piece of the same color
    if (endPiece.type != '.' && startPiece.color == endPiece.color) {
        return false;
    }

    // Check if start and end positions are within the board boundaries
    if (startRow < 0 || startRow >= 8 || startCol < 0 || startCol >= 8 || 
        endRow < 0 || endRow >= 8 || endCol < 0 || endCol >= 8) {
        return false;
    }

    switch (startPiece.type) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            if (startCol == endCol) {  // Moving vertically
                // One square forward move
                if ((startPiece.color == PlayerColor::WHITE && endRow == startRow - 1) ||
                    (startPiece.color == PlayerColor::BLACK && endRow == startRow + 1)) {
                    return endPiece.type == '.';  // Can move forward if the square is empty
                }

                // Two square forward (starting) move 
                else if (startPiece.color == PlayerColor::WHITE && startRow == 6 && endRow == 4) {
                    return endPiece.type == '.';  
                }
                else if (startPiece.color == PlayerColor::BLACK && startRow == 1 && endRow == 3) {
                    return endPiece.type == '.';  
                }
            } else if (abs(startCol - endCol) == 1) {  // Moving diagonally
                if ((startPiece.color == PlayerColor::WHITE && endRow == startRow - 1) ||
                    (startPiece.color == PlayerColor::BLACK && endRow == startRow + 1)) {
                    return endPiece.type != '.';  // Can capture if there's a piece on the square
                }
            }
            break;

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            if ((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) ||
                (abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2)) {
                return true;
            }
            break;
        
        case WHITE_ROOK:
        case BLACK_ROOK:
            if (startRow == endRow) {  // Moving horizontally
                int colStep = (startCol < endCol) ? 1 : -1;
                for (int col = startCol + colStep; col != endCol; col += colStep) {
                    if (board[startRow][col].type != '.') return false;  // Path must be clear
                }
                return true;
            } else if (startCol == endCol) {  // Moving vertically
                int rowStep = (startRow < endRow) ? 1 : -1;
                for (int row = startRow + rowStep; row != endRow; row += rowStep) {
                    if (board[row][startCol].type != '.') return false;  // Path must be clear
                }
                return true;
            }
            break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            if (abs(startRow - endRow) == abs(startCol - endCol)) {
                int rowStep = (startRow < endRow) ? 1 : -1;
                int colStep = (startCol < endCol) ? 1 : -1;
                int row, col;
                for (row = startRow + rowStep, col = startCol + colStep; 
                     row != endRow; 
                     row += rowStep, col += colStep) {
                    if (board[row][col].type != '.') return false;  // Path must be clear
                }
                return true;
            }
            break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            if (startRow == endRow) {  // Moving horizontally
                int colStep = (startCol < endCol) ? 1 : -1;
                for (int col = startCol + colStep; col != endCol; col += colStep) {
                    if (board[startRow][col].type != '.') return false;  // Path must be clear
                }
                return true;
            } else if (startCol == endCol) {  // Moving vertically
                int rowStep = (startRow < endRow) ? 1 : -1;
                for (int row = startRow + rowStep; row != endRow; row += rowStep) {
                    if (board[row][startCol].type != '.') return false;  // Path must be clear
                }
                return true;
            }

            // Diagonal movement
            if (abs(startRow - endRow) == abs(startCol - endCol)) {
                int rowStep = (startRow < endRow) ? 1 : -1;
                int colStep = (startCol < endCol) ? 1 : -1;
                int row, col;
                for (row = startRow + rowStep, col = startCol + colStep; 
                    row != endRow; 
                    row += rowStep, col += colStep) {
                    if (board[row][col].type != '.') return false;  // Path must be clear
                }
                return true;
            }

            break;

        case WHITE_KING:
        case BLACK_KING:
            if (abs(startRow - endRow) <= 1 && abs(startCol - endCol) <= 1) {
                return true;
            }

            // Castling logic
            if (!startPiece.hasMoved && abs(startCol - endCol) == 2) {
                int rookCol = (endCol > startCol) ? 7 : 0;
                Piece rook = board[startRow][rookCol];
                if (rook.type != ((startPiece.color == PlayerColor::WHITE) ? WHITE_ROOK : BLACK_ROOK)) return false;
                if (rook.hasMoved) return false;
                
                // Check if squares between King and Rook are empty
                int step = (rookCol > startCol) ? 1 : -1;
                for (int col = startCol + step; col != rookCol; col += step) {
                    if (board[startRow][col].type != '.') return false;
                }
                
                // Check if the King is not moving through, into, or out of check
                for (int col = startCol; col != endCol; col += step) {
                    ChessBoard tempBoard = *this;
                    tempBoard.board[startRow][startCol] = Piece('.', startPiece.color);
                    tempBoard.board[startRow][col] = startPiece;
                    if (tempBoard.isKingInCheck(startPiece.color)) return false;
                }
                
                return true;
            }
            break;

        default:
            return false;
    }

    return false;
}

const std::vector<std::pair<Piece, std::pair<int, int> > >& ChessBoard::getPieces(PlayerColor color) const {
    return (color == PlayerColor::WHITE) ? whitePieces : blackPieces;
}

bool ChessBoard::isEmpty(int row, int col) const {
    return board[row][col].type == '.';  // Assuming '.' represents an empty square
}

bool ChessBoard::isWhitePieceAt(int row, int col) const {
    return board[row][col].color == PlayerColor::WHITE && board[row][col].type != '.';
}

bool ChessBoard::isInBounds(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool ChessBoard::isKingInCheck(PlayerColor color) const {
    int kingRow = -1;
    int kingCol = -1;
    
    // Determine which list of pieces to check based on the king's color
    const std::vector<std::pair<Piece, std::pair<int, int> > >& piecesToCheck = 
        (color == PlayerColor::WHITE) ? blackPieces : whitePieces;
    
    // Find the King's position in the appropriate piece list
    const std::vector<std::pair<Piece, std::pair<int, int> > >& kingList = 
        (color == PlayerColor::WHITE) ? whitePieces : blackPieces;
    
    for (const auto& pieceWithPos : kingList) {
        const Piece& piece = pieceWithPos.first;
        if (piece.type == (color == PlayerColor::WHITE ? WHITE_KING : BLACK_KING)) {
            kingRow = pieceWithPos.second.first;
            kingCol = pieceWithPos.second.second;
            break;
        }
    }

    if (kingRow == -1) {
        // King's position wasn't found - code error
        return false;
    }

    // For every piece in piecesToCheck, see if it can move to the King's position
    for (const auto& pieceWithPos : piecesToCheck) {
        const Piece& piece = pieceWithPos.first;
        int row = pieceWithPos.second.first;
        int col = pieceWithPos.second.second;

        std::string potentialMove = char(col + 'a') + std::to_string(8 - row) +
                                    char(kingCol + 'a') + std::to_string(8 - kingRow);
    
        if (isValidMoveWithoutCheck(potentialMove)) {
            return true;  // The King is in check by this piece
        }
    }
    return false;  // No piece threatens the King
}

