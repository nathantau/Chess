#ifndef ROOK
#define ROOK

#include "Piece.h"

class Rook : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        virtual vector<pair<int,int>> getValidMoves() const override;
        Rook(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Rook();
        virtual string getName() const override;
        virtual string getSHName() const override;        
    private:
        bool moved;
};

#endif
