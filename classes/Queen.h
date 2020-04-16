#ifndef QUEEN
#define QUEEN

#include "Piece.h"

class Queen : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool is_valid(const int&i, const int& j) const override;
        Queen();
        ~Queen();
    private:
        bool moved;
};

#endif
