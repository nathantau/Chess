#ifndef BOARD
#define BOARD

#include <unordered_set>
#include <iostream>
#include <string>

#include "Piece.cc"
#include "Pawn.cc"
#include "Rook.cc"
#include "Knight.cc"
#include "Bishop.cc"
#include "Queen.cc"
#include "King.cc"

class Board {
    public:
        Board();
        ~Board();
        vector<vector<Piece*>> grid;
        unordered_set<Piece*> black;
        unordered_set<Piece*> white;
        unordered_set<Piece*> deadBlack;
        unordered_set<Piece*> deadWhite;
        MoveStack moveStack;
    private:
        void initPawns();
        void initKings();
        void initQueens();
        void initKnights();
        void initBishops();
        void initRooks();
};

#endif