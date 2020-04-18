#include "King.h"

King::King(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white}, moved{false} {}

King::~King() {}

void King::move(const int& i, const int& j) {}

bool King::isValid(const int&i, const int& j) const { return true; }

vector<pair<int,int>> King::getValidMoves() const {

    vector<pair<int,int>> validMoves{};

    // Moves that validate checking will be done in a higher-level class.

    // Moving
    for (int iDiff = -1; iDiff <= 1; iDiff++) {
        for (int jDiff = -1; jDiff <= 1; jDiff++) {
            if (iDiff != 0 || jDiff != 0) {
                int i{this->i + iDiff};
                int j{this->j + jDiff};
                if (inRange(i, j)) {
                    if (this->grid[i][j] == nullptr || (this->grid[i][j]->white != this->white)) {
                        validMoves.push_back({i, j});
                    }
                }
            }
        }
    }

    // Castleing





    return validMoves;

}


string King::getName() const {
    return "King";
}

string King::getSHName() const {
    return "K";
}