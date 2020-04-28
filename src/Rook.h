#ifndef ROOK
#define ROOK

#include "Piece.h"

class Rook : public Piece {
    public:
        virtual std::vector<std::pair<int,int>> getValidMoves() const override;
        Rook(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Rook();
        virtual std::string getName() const override;
        virtual std::string getSHName() const override;        
    private:
};

#endif
