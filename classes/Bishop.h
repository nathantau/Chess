#ifndef BISHOP
#define BISHOP

#include "Piece.h"

class Bishop : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool is_valid(const int&i, const int& j) const override;
        Bishop();
        ~Bishop();
    private:
        bool moved;
};

#endif
