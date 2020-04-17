#ifndef KING
#define KING

#include "Piece.h"

class King : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        King(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~King();
    private:
        bool moved;
};

#endif
