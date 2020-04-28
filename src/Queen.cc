#include "Queen.h"

Queen::Queen(std::vector<std::vector<Piece*>>& grid, MoveStack& moveStack, const int& i, const int& j, bool white) : Piece{grid, moveStack, i, j, white} {}
Queen::~Queen() {}

std::vector<std::pair<int,int>> Queen::getValidMoves() const {

    std::vector<std::pair<int,int>> validMoves{};

    // Moving Up/Down
    // Moving Diagonally
    std::vector<std::pair<int,int>> iDiffsJDiffs{};
    iDiffsJDiffs.push_back({1, 0});
    iDiffsJDiffs.push_back({-1, 0});
    iDiffsJDiffs.push_back({0, 1});
    iDiffsJDiffs.push_back({0, -1});
    iDiffsJDiffs.push_back({1, 1});
    iDiffsJDiffs.push_back({-1, 1});
    iDiffsJDiffs.push_back({1, -1});
    iDiffsJDiffs.push_back({-1, -1});

    for (const auto& iDiffJDiff : iDiffsJDiffs) {
        const int firstIDiff{iDiffJDiff.first};
        const int firstJDiff{iDiffJDiff.second};
        int iDiff{firstIDiff};
        int jDiff{firstJDiff};
        bool unblocked{true};

        while (unblocked) {
            int i{this->i + iDiff};
            int j{this->j + jDiff};
            iDiff += firstIDiff;
            jDiff += firstJDiff;

            if (inRange(i, j)) {
                if (this->grid[i][j] == nullptr) {
                    // Condition where square is empty
                    validMoves.push_back({i, j});
                } else if (this->grid[i][j]->white == this->white) {
                    // Condition where piece in square is same color
                    unblocked = false;
                } else if (this->grid[i][j]->white != this->white) {
                    // Condition where piece in square is opposite color
                    validMoves.push_back({i, j});
                    unblocked = false;
                }
            } else {
                unblocked = false;
            }
        }
    }

    return validMoves;
}



std::string Queen::getName() const {
    return "Queen";
}

std::string Queen::getSHName() const {
    return "Q";
}