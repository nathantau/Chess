#include "Piece.h"

Piece::Piece(vector<vector<Piece*>>& grid, MoveStack& moveStack, int i, int j, bool white) : grid{grid}, moveStack{moveStack}, i{i}, j{j}, white{white}, alive{true} {}

bool Piece::isAvailable(const int& i, const int& j) const {
    return this->grid[i][j] == nullptr;
}

Piece::~Piece() {}
