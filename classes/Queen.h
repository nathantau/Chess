#ifndef QUEEN
#define QUEEN

#include "Piece.h"

class Queen : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        virtual vector<pair<int,int>> getValidMoves() const override;
        Queen(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~Queen();
        virtual string getName() const override;
        virtual string getSHName() const override;        
    private:
        bool moved;
};

#endif
