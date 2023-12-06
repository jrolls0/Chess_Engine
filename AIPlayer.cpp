#include "AIPlayer.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>


using namespace std;

int numPossibleMoves = 0;

AIPlayer::AIPlayer(PlayerColor color) : color(color) {
    loadOpeningBook();
}

void AIPlayer::loadOpeningBook() {
    std::ifstream file("opening_book.dat");
    std::string line;
    while (std::getline(file, line)) {
        size_t spacePos = line.find(' ');
        openingBook[line.substr(0, spacePos)] = line.substr(spacePos + 1);
    }
}


std::string AIPlayer::moveToString(int startRow, int startCol, int endRow, int endCol) {
    return std::string(1, 'a' + startCol) + std::to_string(8 - startRow) +
           std::string(1, 'a' + endCol) + std::to_string(8 - endRow);
}

void AIPlayer::addIfValidMove(int startRow, int startCol, ChessBoard &board, 
                    std::vector<std::string> &possibleMoves, 
                    int endRow, int endCol) 
{
    std::string move = moveToString(startRow, startCol, endRow, endCol);


    if (board.isValidMove(move)) {
        numPossibleMoves++;
        possibleMoves.push_back(move);
    }
}


std::vector<std::string> AIPlayer::generateAllPossibleMoves(ChessBoard& board, PlayerColor color) {
    std::vector<std::string> possibleMoves;
    
    const auto& pieces = (color == PlayerColor::BLACK) ? board.blackPieces : board.whitePieces;

    for (const auto& piece : pieces) {
        char pieceType = piece.first.type;
        int startRow = piece.second.first;
        int startCol = piece.second.second;

        int direction = (color == PlayerColor::BLACK) ? 1 : -1;

        switch (pieceType) {
            case BLACK_PAWN:
            case WHITE_PAWN:
                addIfValidMove(startRow, startCol, board, possibleMoves, startRow + direction, startCol);
                if ((color == PlayerColor::BLACK && startRow == 1) || (color == PlayerColor::WHITE && startRow == 6)) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + 2 * direction, startCol);
                }
                addIfValidMove(startRow, startCol, board, possibleMoves, startRow + direction, startCol + 1);
                addIfValidMove(startRow, startCol, board, possibleMoves, startRow + direction, startCol - 1);
                break;

            case BLACK_ROOK:
            case WHITE_ROOK:
                for (int i = startRow + direction; i < 8 && i >= 0; i += direction) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, i, startCol);
                }
                for (int i = startRow - direction; i < 8 && i >= 0; i -= direction) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, i, startCol);
                }
                for (int j = startCol + 1; j < 8; ++j) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow, j);
                }
                for (int j = startCol - 1; j >= 0; --j) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow, j);
                }
                break;
            
            case BLACK_KNIGHT:
            case WHITE_KNIGHT: {
                int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
                for (int i = 0; i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + knightMoves[i][0], startCol + knightMoves[i][1]);
                }
                break;
            }

            case BLACK_BISHOP:
            case WHITE_BISHOP: {
                for (int i = 1; startRow + i < 8 && startCol + i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + i, startCol + i);
                }
                for (int i = 1; startRow - i >= 0 && startCol - i >= 0; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow - i, startCol - i);
                }
                for (int i = 1; startRow + i < 8 && startCol - i >= 0; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + i, startCol - i);
                }
                for (int i = 1; startRow - i >= 0 && startCol + i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow - i, startCol + i);
                }
                break;
            }

            case BLACK_QUEEN:
            case WHITE_QUEEN: {
                for (int i = startRow + 1; i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, i, startCol);
                }
                for (int i = startRow - 1; i >= 0; --i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, i, startCol);
                }
                for (int j = startCol + 1; j < 8; ++j) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow, j);
                }
                for (int j = startCol - 1; j >= 0; --j) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow, j);
                }

                // Diagonal moves for the queen
                for (int i = 1; startRow + i < 8 && startCol + i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + i, startCol + i);
                }
                for (int i = 1; startRow - i >= 0 && startCol - i >= 0; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow - i, startCol - i);
                }
                for (int i = 1; startRow + i < 8 && startCol - i >= 0; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + i, startCol - i);
                }
                for (int i = 1; startRow - i >= 0 && startCol + i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow - i, startCol + i);
                }
                break;
            }

            case BLACK_KING:
            case WHITE_KING: {
                int kingMoves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
                for (int i = 0; i < 8; ++i) {
                    addIfValidMove(startRow, startCol, board, possibleMoves, startRow + kingMoves[i][0], startCol + kingMoves[i][1]);
                }
                break;
            }

            default:
                break;
        }
    }

    return possibleMoves;
}


int AIPlayer::evaluateBoard(const ChessBoard& board) {
    int value = 0;

    auto blackPieces = board.blackPieces;
    for (const auto& pieceInfo : blackPieces) {
        int pieceValue = 0;
        char pieceType = pieceInfo.first.type;

        switch (pieceType) {
            case 'p': pieceValue = 1; break;
            case 'n': pieceValue = 3; break;
            case 'b': pieceValue = 3; break;
            case 'r': pieceValue = 5; break;
            case 'q': pieceValue = 9; break;
            case 'k': pieceValue = 1000; break;
        }

        value += pieceValue;  // Subtract value for black pieces
    }

    auto whitePieces = board.whitePieces;
    for (const auto& pieceInfo : whitePieces) {
        int pieceValue = 0;
        char pieceType = pieceInfo.first.type;

        switch (pieceType) {
            case 'P': pieceValue = 1; break;
            case 'N': pieceValue = 3; break;
            case 'B': pieceValue = 3; break;
            case 'R': pieceValue = 5; break;
            case 'Q': pieceValue = 9; break;
            case 'K': pieceValue = 1000; break;
        }

        value -= pieceValue;  // Add value for white pieces
    }

    return value;
}

int AIPlayer::miniMax(ChessBoard &board, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    std::vector<std::string> possibleMoves = generateAllPossibleMoves(board, maximizingPlayer ? PlayerColor::BLACK : PlayerColor::WHITE);

    if (maximizingPlayer) {
        int bestValue = INT_MIN;
        for (const auto& move : possibleMoves) {
            ChessBoard tempBoard = board;
            tempBoard.makeMove(move, PlayerColor::BLACK);
            int moveValue = miniMax(tempBoard, depth - 1, false, alpha, beta);
            bestValue = std::max(bestValue, moveValue);
            alpha = std::max(alpha, moveValue);  // pruning
            if (beta <= alpha) {
                break;  // Beta end
            }
        }
        return bestValue;
    } else {
        int bestValue = INT_MAX;
        for (const auto& move : possibleMoves) {
            ChessBoard tempBoard = board;
            tempBoard.makeMove(move, PlayerColor::WHITE);
            int moveValue = miniMax(tempBoard, depth - 1, true, alpha, beta);
            bestValue = std::min(bestValue, moveValue);
            beta = std::min(beta, moveValue);  // pruning
            if (beta <= alpha) {
                break;  // Alpha end
            }
        }
        return bestValue;
    }
}

std::string AIPlayer::bestMove(ChessBoard &board) {
    std::vector<std::string> possibleMoves = generateAllPossibleMoves(board, PlayerColor::BLACK);
    if (possibleMoves.empty()) {
        cout << "Check Mate!!" << endl;
        exit(1);
    }

    int bestValue = INT_MIN;
    std::string bestMove;
    int alpha = INT_MIN;
    int beta = INT_MAX;

    int totalPieces = board.whitePieces.size() + board.blackPieces.size();
    
    int depth = 3;

    if (totalPieces <= 28) { 
        depth = 4;
    }
    if (totalPieces <= 24) { 
        depth = 5;
    }
    if (totalPieces <= 20) { 
        depth = 6;
    }
    if (totalPieces <= 16) { 
        depth = 7;
    }
    if (totalPieces <= 12) { 
        depth = 8;
    }
    if (totalPieces <= 8) { 
        depth = 9;
    }

    for (const auto& move : possibleMoves) {
        ChessBoard tempBoard = board;
        tempBoard.makeMove(move, PlayerColor::BLACK);
        int moveValue = miniMax(tempBoard, depth, false, alpha, beta);

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }
    
    return bestMove;
}

std::string AIPlayer::getMove(ChessBoard& board, const std::string& move) {
    // Check if the moves are in the opening book
    if (opening && openingBook.find(move) != openingBook.end()) {
        std::string botMove =  openingBook[move];
        board.makeMove(botMove, PlayerColor::BLACK);
        opening = false;
    
        return botMove;
    }
    
    string result= bestMove(board);
    cout << "Opponent's Move:" << result << endl;
    board.makeMove(result,PlayerColor::BLACK);

    return result;
}



