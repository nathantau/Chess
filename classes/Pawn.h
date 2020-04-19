#ifndef PAWN
#define PAWN

#include "Piece.h"

class Pawn : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        virtual vector<pair<int,int>> getValidMoves() const override;
        Pawn(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Pawn();
        virtual string getName() const override;
        virtual string getSHName() const override;
    private:
};

#endif
