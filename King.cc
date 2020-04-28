#include "King.h"
#include <iostream>

King::King(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

King::~King() {}

std::vector<std::pair<int,int>> King::getValidMoves() const {

    std::vector<std::pair<int,int>> validMoves{};

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
    // The movement of the corresponding Rook will be handled in the main method
    if (this->numMoves == 0) {
        // Condition where king is unmoved
        if (this->white) {
            if (this->grid[7][7] != nullptr && this->grid[7][7]->white && this->grid[7][7]->getNumMoves() == 0) {
                // Condition where King's Rook has not moved yet
                if (this->grid[7][5] == nullptr && this->grid[7][6] == nullptr) {
                    // Condition where bishop and knight have moved somewhere else
                    validMoves.push_back({7, 6});
                }
            }
            if (this->grid[7][0] != nullptr && this->grid[7][7]->white && this->grid[7][0]->getNumMoves() == 0) {
                // Condition where Queen's Rook has not moved yet
                if (this->grid[7][1] == nullptr && this->grid[7][2] == nullptr && this->grid[7][3]) {
                    // Condition where bishop and knight have moved somewhere else
                    validMoves.push_back({7, 2});
                }                
            }
        } else {
            if (this->grid[0][7] != nullptr && !this->grid[7][7]->white && this->grid[0][7]->getNumMoves() == 0) {
                // Condition where King's Rook has not moved yet
                if (this->grid[0][5] == nullptr && this->grid[0][6] == nullptr) {
                    // Condition where bishop and knight have moved somewhere else
                    validMoves.push_back({0, 6});
                }
            }
            if (this->grid[0][0] != nullptr && !this->grid[7][7]->white && this->grid[0][0]->getNumMoves() == 0) {
                // Condition where Queen's Rook has not moved yet
                if (this->grid[0][1] == nullptr && this->grid[0][2] == nullptr && this->grid[0][3]) {
                    // Condition where bishop and knight have moved somewhere else
                    validMoves.push_back({0, 2});
                }                
            }            
        }
    }
    return validMoves;
}

std::string King::getName() const {
    return "King";
}

std::string King::getSHName() const {
    return "K";
}