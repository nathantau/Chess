#include "Knight.h"

Knight::Knight(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}

Knight::~Knight() {}

std::vector<std::pair<int,int>> Knight::getValidMoves() const {

    std::vector<std::pair<int,int>> validMoves{};

    std::vector<std::pair<int,int>> iDiffsJDiffs;
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

std::string Knight::getName() const {
    return "Knight";
}

std::string Knight::getSHName() const {
    return "k";
}