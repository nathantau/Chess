#include "Rook.h"

Rook::Rook(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white}, moved{false} {}

Rook::~Rook() {}

void Rook::move(const int& i, const int& j) {}

bool Rook::isValid(const int&i, const int& j) const { 
    
    

    
    return true; 
}

vector<pair<int,int>> Rook::getValidMoves() const {

    vector<pair<int,int>> validMoves{};

    // Moving Up/Down
    int iDiff = 1;
    bool unblocked{true};
    while (unblocked) {
        int i{this->i + iDiff};
        iDiff += 1;
        if (inRange(i, this->j)) {
            if (this->grid[i][this->j] == nullptr) {
                validMoves.push_back({i, this->j});
            } else if (this->grid[i][this->j]->white == this->white) {
                // Condition where piece is same color
                break;
            } else if (this->grid[i][this->j]->white != this->white) {
                // Condition where piece is opposite color
                validMoves.push_back({i, this->j});
                break;
            }
        }
    }
    iDiff = -1;
    unblocked = true;
    while (unblocked) {
        int i{this->i + iDiff};
        iDiff -= 1;
        if (inRange(i, this->j)) {
            if (this->grid[i][this->j] == nullptr) {
                validMoves.push_back({i, this->j});
            } else if (this->grid[i][this->j]->white == this->white) {
                // Condition where piece is same color
                break;
            } else if (this->grid[i][this->j]->white != this->white) {
                // Condition where piece is opposite color
                validMoves.push_back({i, this->j});
                break;
            }
        }
    }

    // Moving Left/Right
    int jDiff = 1;
    unblocked = true;
    while (unblocked) {
        int j{this->j + jDiff};
        jDiff += 1;
        if (inRange(this->i, j)) {
            if (this->grid[this->i][j] == nullptr) {
                validMoves.push_back({i, this->j});
            } else if (this->grid[this->i][j]->white == this->white) {
                // Condition where piece is same color
                break;
            } else if (this->grid[this->i][j]->white != this->white) {
                // Condition where piece is opposite color
                validMoves.push_back({this->i, j});
                break;
            }
        }
    }
    iDiff = -1;
    unblocked = true;
    while (unblocked) {
        int j{this->j + jDiff};
        jDiff -= 1;
        if (inRange(this->i, j)) {
            if (this->grid[this->i][j] == nullptr) {
                validMoves.push_back({i, this->j});
            } else if (this->grid[this->i][j]->white == this->white) {
                // Condition where piece is same color
                break;
            } else if (this->grid[this->i][j]->white != this->white) {
                // Condition where piece is opposite color
                validMoves.push_back({this->i, j});
                break;
            }
        }
    }

    return validMoves;
}
