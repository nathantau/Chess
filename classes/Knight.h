#ifndef KNIGHT
#define KNIGHT

#include "Piece.h"

class Knight : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        Knight(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Knight();
    private:
        bool moved;
};

#endif
