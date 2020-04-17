#include "Queen.h"

Queen::Queen(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

void Queen::move(const int& i, const int& j) {
    
}

bool Queen::isValid(const int&i, const int& j) const {
    return true;
}

Queen::~Queen() {}