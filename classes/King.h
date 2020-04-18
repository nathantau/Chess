#ifndef KING
#define KING

#include "Piece.h"

class King : public Piece {
    public:
        virtual void move(const int& i, const int& j) override;
        virtual bool isValid(const int&i, const int& j) const override;
        virtual vector<pair<int,int>> getValidMoves() const override;
        King(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white);
        ~King();
        virtual string getName() const override;
        virtual string getSHName() const override;        
    private:
        bool moved;
};

#endif
