#ifndef KNIGHT
#define KNIGHT

#include "Piece.h"

class Knight : public Piece {
    public:
        virtual std::vector<std::pair<int,int>> getValidMoves() const override;
        Knight(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Knight();
        virtual std::string getName() const override;
        virtual std::string getSHName() const override;
    private:
};

#endif
