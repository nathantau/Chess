#include "Board.cc"

using namespace std;

void move(Piece* piece, Board* board, const int& i, const int& j);

int main() {
    
    Board b{};

    bool whiteTurn{true};
    bool gameOver{false};

    string input;
    int i;
    int j;

    while (!gameOver) {

        Piece* piece{nullptr};

        do {
            cout << "Please enter piece's position like so {i} {j}" << endl;
            cin >> i >> j;
            piece = b.grid[i][j];
        } while (piece == nullptr || piece->white != whiteTurn || piece->getValidMoves().size() == 0);

        for (const auto& iJ : piece->getValidMoves()) {
            cout << iJ.first << " " << iJ.second << endl;
        }

        cout << "-----------------" << endl;

        whiteTurn = !whiteTurn;

    }





}




void move(Piece* piece, Board* board, const int& i, const int& j) {




}