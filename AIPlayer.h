#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "board.h"
#include <map>
#include <string>

class AIPlayer {
public:
    AIPlayer(PlayerColor color);
    
    std::string getMove(ChessBoard& board, const std::string& move);
    std::vector<std::string> generateAllPossibleMoves(ChessBoard& board, PlayerColor color); 
    std::string moveToString(int startRow, int startCol, int endRow, int endCol);
    std::string bestMove(ChessBoard& board);
    int evaluateBoard(const ChessBoard& board);
    void addIfValidMove(int startRow, int startCol, ChessBoard &board, 
                    std::vector<std::string> &possibleMoves, 
                    int endRow, int endCol);
    int miniMax(ChessBoard &board, int depth, bool maximizingPlayer, int alpha, int beta);

private:
    PlayerColor color;
    bool opening = true;
    std::map<std::string, std::string> openingBook;

    void loadOpeningBook();
};

#endif // AI_PLAYER_H
