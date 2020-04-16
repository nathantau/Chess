#ifndef BOARD
#define BOARD

#include <unordered_set>

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

    private:
        void init_pawns();
        void init_kings();
        void init_queens();
        void init_knights();
        void init_bishops();
        void init_rooks();
        vector<vector<Piece*>> grid;
        unordered_set<Piece*> black;
        unordered_set<Piece*> white;
};

#endif