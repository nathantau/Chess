#include "Piece.cc"
#include "Pawn.h"

Pawn::Pawn(vector<vector<Piece*>>& grid, const int& i, const int& j, bool white, void moved) : Piece{grid, i, j white}, moved{false} {}

Pawn::~Pawn() {}

bool Pawn::move(const int& i, const int& j) {
    
}

bool Pawn::is_valid(const int&i, const int& j) const {
    if (!(i >= 0 && i <= 7 && j >= 0 && j <= 7)) {
        return false;
    }
    if (this->white) {
        // moving forward
        if (this->i == i) {
            if (this->j - j == 2 && !this->moved) {
                if (is_available(i, j)) {

                }
                this->moved = true;
                return true;
            } else if (this->j - j == 1) {
                if (is_available())
            }
        }

    } else {

    }


    if (this->moved) {
        if (this->i == i) {

        } else if (this->i == )
    } else {

    }
    return false;
}
