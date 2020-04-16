#include "Board.h"

Board::Board() : grid{vector<vector<Piece*>>(8, vector<Piece*>(8, nullptr))} {
    init_pawns();
    init_rooks();
    init_knights();
    init_bishops();
    init_kings();
    init_queens();
}

Board::~Board() {
    for (auto& piece : this->black) {
        delete piece;
        piece = nullptr;
    }
    for (auto& piece: this->white) {
        delete piece;
        piece = nullptr;
    }
}

void Board::init_queens() {
    Piece* temp{new Queen{}};
    this->black.insert(temp);
    this->grid[0][3] = left;
    temp = new Queen{};
    this->white.insert(temp);
    this->grid[7][3] = temp;
}

void Board::init_kings() {
    Piece* temp{new King{}};
    this->black.insert(temp);
    this->grid[0][5] = left;
    temp = new King{};
    this->white.insert(temp);
    this->grid[7][5] = temp;
}

void Board::init_knights() {
    Piece* left{new Knight{}};
    Piece* right{new Knight{}};
    this->black.insert(left);
    this->black.insert(right);
    this->grid[0][2] = left;
    this->grid[0][5] = right;    
    left = new Knight{};
    right = new Knight{};
    this->white.insert(left);
    this->white.insert(right);
    this->grid[7][2] = left;
    this->grid[7][5] = right;
}

void Board::init_bishops() {
    Piece* left{new Bishop{}};
    Piece* right{new Bishop{}};
    this->black.insert(left);
    this->black.insert(right);
    this->grid[0][1] = left;
    this->grid[0][6] = right;    
    left = new Bishop{};
    right = new Bishop{};
    this->white.insert(left);
    this->white.insert(right);
    this->grid[7][1] = left;
    this->grid[7][6] = right;
}

void Board::init_rooks() {
    Piece* left{new Rook{}};
    Piece* right{new Rook{}};
    this->black.insert(left);
    this->black.insert(right);
    this->grid[0][0] = left;
    this->grid[0][7] = right;    
    left = new Rook{};
    right = new Rook{};
    this->white.insert(left);
    this->white.insert(right);
    this->grid[7][0] = left;
    this->grid[7][7] = right;
}

void Board::init_pawns() {
    Piece* temp{nullptr};
    for (auto i{0}; i < 8; i++) {
        temp = new Pawn{};
        this->black.insert(temp);
        this->grid[1][i] = temp;
        temp = new Pawn{};
        this->white.insert(temp);
        this->grid[1][i] = temp;
    }
}