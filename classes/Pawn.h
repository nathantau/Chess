#ifndef PAWN
#define PAWN

#include "Piece.h"

class Pawn : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool is_valid(const int&i, const int& j) const override;
        Pawn();
        ~Pawn();
    private:
        bool moved;
};

#endif
