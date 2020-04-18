#include "Knight.h"

Knight::Knight(vector<vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

Knight::~Knight() {}

void Knight::move(const int& i, const int& j) {}

bool Knight::isValid(const int&i, const int& j) const { return true; }

vector<pair<int,int>> Knight::getValidMoves() const {

    vector<pair<int,int>> validMoves{};

    vector<pair<int,int>> iDiffsJDiffs;
    iDiffsJDiffs.push_back({1, 2});
    iDiffsJDiffs.push_back({1, -2});
    iDiffsJDiffs.push_back({-1, 2});
    iDiffsJDiffs.push_back({-1, -2});
    iDiffsJDiffs.push_back({2, 1});
    iDiffsJDiffs.push_back({2, -1});
    iDiffsJDiffs.push_back({-2, 1});
    iDiffsJDiffs.push_back({-2, -1});

    for (const auto& iDiffJDiff : iDiffsJDiffs) {
        const int i{this->i + iDiffJDiff.first};
        const int j{this->j + iDiffJDiff.second};

        if (inRange(i, j)) {
            if (this->grid[i][j] == nullptr) {
                validMoves.push_back({i, j});
            } else if (this->grid[i][j]->white != this->white) {
                validMoves.push_back({i, j});
            }
        }
    }

    return validMoves;
}

string Knight::getName() const {
    return "Knight";
}

string Knight::getSHName() const {
    return "k";
}