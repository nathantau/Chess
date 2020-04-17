#include "Rook.h"

Rook::Rook(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white}, moved{false} {}

Rook::~Rook() {}

void Rook::move(const int& i, const int& j) {}

bool Rook::isValid(const int&i, const int& j) const { 
    
    

    
    return true; 
}