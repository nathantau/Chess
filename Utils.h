#ifndef UTILS
#define UTILS

#include <vector>
#include "Board.h"
#include "Piece.h"

class Utils {
    public:
        static void movePiece(Piece* piece, Board& board, const int& i, const int& j, bool test = false);
        static void printBoard(Board& board);
        static bool inCheck(Piece* king, Board& board);
        static std::vector<std::pair<int,int>> filterCheckedMoves(Piece* king, Piece* piece, std::vector<std::pair<int,int>> validMoves, Board& board);
        static void castle(Piece* piece, const int& i, const int& j, Board& board);
        static void undoMove(Board& board);
        static void undoCastle(Board& board);
        static void enPassant(Piece* piece, const int& i, const int& j, Board& board);
        static bool promote(Piece* piece, const int& i, const int& j, Board& board, bool test);
};

#endif