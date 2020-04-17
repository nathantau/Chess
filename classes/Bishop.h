#ifndef BISHOP
#define BISHOP

#include "Piece.h"

class Bishop : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        Bishop(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Bishop();
    private:
        bool moved;
};

#endif
