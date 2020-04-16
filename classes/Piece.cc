Piece::Piece(vector<vector<Piece*>>& grid, int i, int j, bool white) : grid{grid}, i{i}, j{j}, white{white}, alive{true} {}

bool Piece::is_available(const int& i, const int& j) {
    return this->grid[i][j] == nullptr;
}
