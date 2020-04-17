#include "King.h"

King::King(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white}, moved{false} {}

King::~King() {}

void King::move(const int& i, const int& j) {}

bool King::isValid(const int&i, const int& j) const { return true; }