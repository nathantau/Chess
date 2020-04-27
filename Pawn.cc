#include "Pawn.h"

bool inRange(const int& i, const int& j);

Pawn::Pawn(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

Pawn::~Pawn() {}

std::vector<std::pair<int,int>> Pawn::getValidMoves() const {

    std::vector<std::pair<int,int>> validMoves{};

    if (inRange(this->i - (this->white ? 1 : -1), this->j)) {
        // Condition where pawn moves forward
        if (this->grid[this->i - (this->white ? 1 : -1)][j] == nullptr) {
            // Condition where square in front is empty
            validMoves.push_back({this->i - (this->white ? 1 : -1), this->j});
            if (inRange(this->i - (this->white ? 2 : -2), j) && this->getNumMoves() == 0) {
                if (this->grid[this->i - (this->white ? 2 : -2)][j] == nullptr) {
                    // Condition where square two spaces ahead is empty
                    validMoves.push_back({this->i - (this->white ? 2 : -2), j});
                }
            }
        }
        // Conditions where pawn attacks upper diagonal squares
        if (inRange(this->i - (this->white ? 1 : -1), this->j + 1)) {
            Piece* piece{this->grid[this->i - (this->white ? 1 : -1)][this->j + 1]};
            if (piece != nullptr && piece->white != this->white) {
                validMoves.push_back({this->i - (this->white ? 1 : -1), this->j + 1});
            }
        }
        if (inRange(this->i - (this->white ? 1 : -1), this->j - 1)) {
            Piece* piece{this->grid[this->i - (this->white ? 1 : -1)][this->j - 1]};
            if (piece != nullptr && piece->white != this->white) {
                validMoves.push_back({this->i - (this->white ? 1 : -1), this->j - 1});
            }
        }
    }

    if (!this->moveStack.empty()) {
        std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>> lastMove{this->moveStack.back()};
        if (std::get<0>(lastMove)->getSHName() == "p" && std::get<0>(lastMove)->white != this->white) {
            // Condition where piece is pawn and pieces are opposite colors
            if (std::abs(std::get<2>(lastMove).first - std::get<3>(lastMove).first) == 2 && std::abs(std::get<3>(lastMove).second - this->j) == 1 && this->i == std::get<3>(lastMove).first) {
                // Condition where pawn moved two steps forward and is beside this pawn
                if (this->grid[this->white ? this->i - 1 : this->i + 1][std::get<3>(lastMove).second] == nullptr) {
                    // Condition where destination is empty
                    // Note that En Passant will always be in range so the check is not needed
                    validMoves.push_back({this->white ? this->i - 1 : this->i + 1, std::get<3>(lastMove).second});
                }
            }
        }
    }

    return validMoves;
}

std::string Pawn::getName() const {
    return "Pawn";
}

std::string Pawn::getSHName() const {
    return "p";
}