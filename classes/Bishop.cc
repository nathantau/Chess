#include "Bishop.h"

Bishop::Bishop(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

void Bishop::move(const int& i, const int& j) {
    
}

bool Bishop::isValid(const int&i, const int& j) const {
    return true;
}

Bishop::~Bishop() {}