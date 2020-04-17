#ifndef QUEEN
#define QUEEN

#include "Piece.h"

class Queen : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        Queen(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Queen();
    private:
        bool moved;
};

#endif
