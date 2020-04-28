#ifndef QUEEN
#define QUEEN

#include "Piece.h"

class Queen : public Piece {
    public:
        virtual std::vector<std::pair<int,int>> getValidMoves() const override;
        Queen(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Queen();
        virtual std::string getName() const override;
        virtual std::string getSHName() const override;        
    private:
};

#endif
