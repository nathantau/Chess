#include "Board.h"

Board::Board() : grid{vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr))} {
    initPawns();
    initRooks();
    initKnights();
    initBishops();
    initKings();
    initQueens();
}

Board::~Board() {
    for (auto& piece : this->black) {
        delete piece;
    }
    this->black.clear();
    for (auto& piece: this->white) {
        delete piece;
    }
    this->white.clear();
}

void Board::initQueens() {
    Piece* temp{new Queen{this->grid, this->moveStack, 0, 3, false}};
    this->black.insert(temp);
    this->grid[0][3] = temp;
    temp = new Queen{this->grid, this->moveStack, 7, 3, true};
    this->white.insert(temp);
    this->grid[7][3] = temp;
}

void Board::initKings() {
    Piece* temp{new King{this->grid, this->moveStack, 0, 4, false}};
    this->black.insert(temp);
    this->grid[0][4] = temp;
    temp = new King{this->grid, this->moveStack, 7, 4, true};
    this->white.insert(temp);
    this->grid[7][4] = temp;
}

void Board::initKnights() {
    Piece* left{new Knight{this->grid, this->moveStack, 0, 1, false}};
    Piece* right{new Knight{this->grid, this->moveStack, 0, 6, false}};
    this->black.insert(left);
    this->black.insert(right);
    this->grid[0][1] = left;
    this->grid[0][6] = right;    
    left = new Knight{this->grid, this->moveStack, 7, 1, true};
    right = new Knight{this->grid, this->moveStack, 7, 6, true};
    this->white.insert(left);
    this->white.insert(right);
    this->grid[7][1] = left;
    this->grid[7][6] = right;
}

void Board::initBishops() {
    Piece* left{new Bishop{this->grid, this->moveStack, 0, 2, false}};
    Piece* right{new Bishop{this->grid, this->moveStack, 0, 5, false}};
    this->black.insert(left);
    this->black.insert(right);
    this->grid[0][2] = left;
    this->grid[0][5] = right;    
    left = new Bishop{this->grid, this->moveStack, 7, 2, true};
    right = new Bishop{this->grid, this->moveStack, 7, 5, true};
    this->white.insert(left);
    this->white.insert(right);
    this->grid[7][2] = left;
    this->grid[7][5] = right;
}

void Board::initRooks() {
    Piece* left{new Rook{this->grid, this->moveStack, 0, 0, false}};
    Piece* right{new Rook{this->grid, this->moveStack, 0, 7, false}};
    this->black.insert(left);
    this->black.insert(right);
    this->grid[0][0] = left;
    this->grid[0][7] = right;    
    left = new Rook{this->grid, this->moveStack, 7, 0, true};
    right = new Rook{this->grid, this->moveStack, 7, 7, true};
    this->white.insert(left);
    this->white.insert(right);
    this->grid[7][0] = left;
    this->grid[7][7] = right;
}

void Board::initPawns() {
    Piece* temp{nullptr};
    for (auto i{0}; i < 8; i++) {
        temp = new Pawn{this->grid, this->moveStack, 1, i, false};
        this->black.insert(temp);
        this->grid[1][i] = temp;
        temp = new Pawn{this->grid, this->moveStack, 6, i, true};
        this->white.insert(temp);
        this->grid[6][i] = temp;
    }
}