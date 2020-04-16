#ifndef KNIGHT
#define KNIGHT

#include "Piece.h"

class Knight : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool is_valid(const int&i, const int& j) const override;
        Knight();
        ~Knight();
    private:
        bool moved;
};

#endif
