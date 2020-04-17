#ifndef PAWN
#define PAWN

#include "Piece.h"

class Pawn : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        Pawn(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Pawn();
    private:
        bool moved;
};

#endif
