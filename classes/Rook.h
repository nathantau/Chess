#ifndef ROOK
#define ROOK

#include "Piece.h"

class Rook : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool is_valid(const int&i, const int& j) const override;
        Rook();
        ~Rook();
    private:
        bool moved;
};

#endif
