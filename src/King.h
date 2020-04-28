#ifndef KING
#define KING

#include "Piece.h"

class King : public Piece {
    public:
        virtual std::vector<std::pair<int,int>> getValidMoves() const override;
        King(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~King();
        virtual std::string getName() const override;
        virtual std::string getSHName() const override;        
    private:
};

#endif
