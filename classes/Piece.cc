#include "Piece.h"

Piece::Piece(vector<vector<Piece*>>& grid, MoveStack& moveStack, int i, int j, bool white) : grid{grid}, moveStack{moveStack}, i{i}, j{j}, white{white}, alive{true} {}

bool Piece::isAvailable(const int& i, const int& j) const {
    return this->grid[i][j] == nullptr;
}

bool Piece::inRange(const int& i, const int& j) const {
    if (i >= 0 && i <= 7 && j >= 0 && j <= 7) {
        return true;
    }
    return false;
}

Piece::~Piece() {}
