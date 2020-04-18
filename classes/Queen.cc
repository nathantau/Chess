#include "Queen.h"

Queen::Queen(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}
Queen::~Queen() {}

void Queen::move(const int& i, const int& j) {
    
}

bool Queen::isValid(const int&i, const int& j) const {
    return true;
}

vector<pair<int,int>> Queen::getValidMoves() const {

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
    jDiff = -1;
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

    // Moving diagonally
    vector<pair<int,int>> iDiffsJDiffs{};
    iDiffsJDiffs.push_back({1, 1});
    iDiffsJDiffs.push_back({-1, 1});
    iDiffsJDiffs.push_back({1, -1});
    iDiffsJDiffs.push_back({-1, -1});

    for (const auto& iDiffJDiff : iDiffsJDiffs) {
        const int firstIDiff{iDiffJDiff.first};
        const int firstJDiff{iDiffJDiff.second};
        int iDiff{firstIDiff};
        int jDiff{firstJDiff};
        unblocked = true;

        while (unblocked) {
            int i{this->i + iDiff};
            int j{this->j + jDiff};
            iDiff += firstIDiff;
            jDiff += firstJDiff;
            if (inRange(this->i, j)) {
                if (this->grid[i][j] == nullptr) {
                    // Condition where square is empty
                    validMoves.push_back({i, j});
                } else if (this->grid[i][j]->white == this->white) {
                    // Condition where piece in square is same color
                    break;
                } else if (this->grid[i][j]->white != this->white) {
                    // Condition where piece in square is opposite color
                    validMoves.push_back({i, j});
                    break;
                }
            }
        }
    }

    return validMoves;
}



string Queen::getName() const {
    return "Queen";
}

string Queen::getSHName() const {
    return "Q";
}