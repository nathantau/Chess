#ifndef PAWN
#define PAWN

#include "Piece.h"

class King : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool is_valid(const int&i, const int& j) const override;
        King();
        ~King();
    private:
        bool moved;
};

#endif
