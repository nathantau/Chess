#include "Knight.h"

Knight::Knight(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

Knight::~Knight() {}

void Knight::move(const int& i, const int& j) {}

bool Knight::isValid(const int&i, const int& j) const { return true; }