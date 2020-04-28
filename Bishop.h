#ifndef BISHOP
#define BISHOP

#include "Piece.h"

class Bishop : public Piece {
    public:
        virtual std::vector<std::pair<int,int>> getValidMoves() const override;
        Bishop(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Bishop();
        virtual std::string getName() const override;
        virtual std::string getSHName() const override;        
    private:
};

#endif
