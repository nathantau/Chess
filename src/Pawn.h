#ifndef PAWN
#define PAWN

#include "Piece.h"

class Pawn : public Piece {
    public:
        virtual std::vector<std::pair<int,int>> getValidMoves() const override;
        Pawn(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Pawn();
        virtual std::string getName() const override;
        virtual std::string getSHName() const override;
    private:
};

#endif
