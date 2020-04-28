#ifndef BOARD
#define BOARD

#include <unordered_set>
#include <iostream>
#include <string>

#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class Board {
    public:
        Board();
        ~Board();
        std::vector<std::vector<Piece*>> grid;
        std::unordered_set<Piece*> black;
        std::unordered_set<Piece*> white;
        std::unordered_set<Piece*> deadBlack;
        std::unordered_set<Piece*> deadWhite;
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