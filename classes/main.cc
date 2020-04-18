#include "Board.cc"

using namespace std;

void movePiece(Piece* piece, Board& board, const int& i, const int& j);
void printBoard(Board& board);

int main() {
    
    Board board{};

    bool whiteTurn{true};
    bool gameOver{false};

    string input;
    int i;
    int j;


    while (!gameOver) {
        
        printBoard(board);

        Piece* piece{nullptr};
        cout << (whiteTurn ? "White's Turn: " : "Black's Turn: ") << endl;

        do {
            cout << "Please enter piece's position like so {i} {j}" << endl;
            cin >> i >> j;
            piece = board.grid[i][j];
        } while (piece == nullptr || piece->white != whiteTurn || piece->getValidMoves().size() == 0);

        cout << "Possible moves for " << piece->getName() << endl;

        vector<pair<int,int>> validMoves = piece->getValidMoves();

        for (int i{0}; i < validMoves.size(); i++) {
            cout << "(" << i + 1 << ")" << validMoves[i].first << " " << validMoves[i].second << endl;
        }

        int move;
        do {
            cin >> move;
            move -= 1;
        } while (move < 0 || move >= validMoves.size());

        movePiece(piece, board, validMoves[move].first, validMoves[move].second);

        // Swap turns
        whiteTurn = !whiteTurn;

    }
}

void printBoard(Board& board) {
    cout << "  | 0 1 2 3 4 5 6 7" << endl;
    cout << "-------------------" << endl;
    int i{0};
    for (const auto& row : board.grid) {
        cout << i << " | ";
        for (const auto& square : row) {
            if (square == nullptr) {
                cout << "  ";
            } else {
                cout << square->getSHName() << " ";
            }
        }
        i++;
        cout << endl;
    }
    cout << endl;
}


void movePiece(Piece* piece, Board& board, const int& i, const int& j) {

    // Moves that leave the King in check are not taking into account as of yet
    Piece* newPos{board.grid[i][j]};

    board.moveStack.push_back({piece, {piece->getPos(), {i, j}}});
    board.grid[piece->getPos().first][piece->getPos().second] = nullptr;
    
    
    
    cout << piece->getPos().first << piece->getPos().second << endl;




    if (newPos == nullptr) {
        board.grid[i][j] = piece;
        piece->updatePos(i, j);
    } else {
        // Condition where a piece of the opposite color is in the square of interest
        if (piece->white) {
            board.deadBlack.insert(newPos);
        } else {
            board.deadWhite.insert(newPos);
        }
        piece->updatePos(i, j);
        board.grid[i][j] = piece;
    }

}