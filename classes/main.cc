#include "Board.cc"

using namespace std;

void movePiece(Piece* piece, Board& board, const int& i, const int& j);
void printBoard(Board& board);
bool inCheck(Piece* king, Board& board);
vector<pair<int,int>> filterCheckedMoves(Piece* king, Piece* piece, vector<pair<int,int>> validMoves, Board& board);
void castle(Piece* piece, const int& i, const int& j, Board& board);
void undoCastle(Board& board);

int main() {
    
    Board board{};

    bool whiteTurn{true};
    bool gameOver{false};

    string input;
    int i;
    int j;

    Piece* whiteKing{board.grid[7][4]};
    Piece* blackKing{board.grid[0][4]};

    bool checked{false};

    while (!gameOver) {
        
        printBoard(board);

        Piece* piece{nullptr};

        if (checked) {
            // Condition where player is in check. A full search over the alive
            // pieces of the player's color will determine if any valid moves
            // (filtered) exist. If not, CHECKMATE!
            int numValidMoves{0};
            if (whiteTurn) {
                for (const auto& whitePiece : board.white) {
                    if (board.deadWhite.count(whitePiece) == 0) {
                        // Condiiton where white piece is alive
                        numValidMoves += filterCheckedMoves(whiteKing, whitePiece, whitePiece->getValidMoves(), board).size();
                    }
                }
                if (numValidMoves == 0) {
                    cout << "Black wins!!!" << endl;
                    gameOver = true;
                }
            } else {
                for (const auto& blackPiece : board.black) {
                    if (board.deadBlack.count(blackPiece) == 0) {
                        // Condiiton where white piece is alive
                        numValidMoves += filterCheckedMoves(blackKing, blackPiece, blackPiece->getValidMoves(), board).size();
                    }
                }
                if (numValidMoves == 0) {
                    cout << "White wins!!!" << endl;
                    gameOver = true;
                }
            }
        }

        cout << (whiteTurn ? "White's Turn: " : "Black's Turn: ") << endl;

        vector<pair<int,int>> validMoves;
        do {
            cout << "Please enter piece's position like so {i} {j}" << endl;
            cin >> i >> j;
            piece = board.grid[i][j];
        } while (piece == nullptr || piece->white != whiteTurn || (validMoves = filterCheckedMoves(piece->white ? whiteKing : blackKing, piece, piece->getValidMoves(), board)).size() == 0);

        cout << "Possible moves for " << (whiteTurn ? "White " : "Black ") << piece->getName() << endl;

        // vector<pair<int,int>> validMoves = filterCheckedMoves(piece->white ? whiteKing : blackKing, piece, piece->getValidMoves(), board);

        for (int i{0}; i < validMoves.size(); i++) {
            cout << "(" << i + 1 << ") " << validMoves[i].first << " " << validMoves[i].second << endl;
        }

        int move;
        do {
            cin >> move;
            move -= 1;
        } while (move < 0 || move >= validMoves.size());

        movePiece(piece, board, validMoves[move].first, validMoves[move].second);

        if (inCheck(whiteTurn ? blackKing : whiteKing, board)) {
            checked = true;
            cout << "Check!" << endl;
        } else {
            checked = false;
        }

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
                cout << square->getSHName();
                if (square->white) {
                    cout << "*";
                } else {
                    cout << " ";
                }
            }
        }
        i++;
        cout << endl;
    }
    cout << endl;
}


void movePiece(Piece* piece, Board& board, const int& i, const int& j) {

    Piece* newPos{board.grid[i][j]};

    // Update stack of moves (piece being moved, piece at new position, and position updates)
    board.moveStack.push_back({piece, newPos, piece->getPos(), {i, j}});
    
    if (newPos == nullptr) {
        // Rook moves only if the conditions for castling are satisfied
        castle(piece, i, j, board);
        board.grid[piece->getPos().first][piece->getPos().second] = nullptr;
        board.grid[i][j] = piece;
        piece->updatePos(i, j);
    } else {
        // Condition where a piece of the opposite color is in the square of interest
        board.grid[piece->getPos().first][piece->getPos().second] = nullptr;
        if (piece->white) {
            board.deadBlack.insert(newPos);
        } else {
            board.deadWhite.insert(newPos);
        }
        piece->updatePos(i, j);
        board.grid[i][j] = piece;
    }

}

void undoMove(Board& board) {

    Piece* piece{get<0>(board.moveStack.back())};
    Piece* killed{get<1>(board.moveStack.back())};
    const pair<int,int> initPos{get<2>(board.moveStack.back())};
    const pair<int,int> finPos{get<3>(board.moveStack.back())};

    undoCastle(board);

    if (killed != nullptr) {
        (piece->white ? board.deadBlack : board.deadWhite).erase(killed);
    }

    // Internal update of position
    piece->updatePos(initPos.first, initPos.second, true);

    // Update positioning according to grid
    board.grid[initPos.first][initPos.second] = piece;
    board.grid[finPos.first][finPos.second] = killed;
}

bool inCheck(Piece* king, Board& board) {

    // Strategy: Get the position of the king,
    // and compare the valid moves of all the other 
    // pieces of the opposite color and see if they
    // coincide. If so, then the king is being Checked.

    pair<int,int> kingPos{king->getPos()};

    if (king->white) {
        for (const auto& blackPiece : board.black) {
            for (const auto& move : blackPiece->getValidMoves()) {
                if (move == kingPos) {
                    return true;
                }
            }
        }
    } else {
        for (const auto& whitePiece : board.white) {
            for (const auto& move : whitePiece->getValidMoves()) {
                if (move == kingPos) {
                    return true;
                }
            }
        }
    }
    return false;
}

vector<pair<int,int>> filterCheckedMoves(Piece* king, Piece* piece, vector<pair<int,int>> validMoves, Board& board) {

    pair<int,int> piecePos{piece->getPos()};
    vector<pair<int,int>> filteredMoves;

    for (const auto& move : validMoves) {
        movePiece(piece, board, move.first, move.second);
        if (!inCheck(king, board)) {
            filteredMoves.push_back(move);
        }
        undoMove(board);
    }
    return filteredMoves;
}

void castle(Piece* piece, const int& i, const int& j, Board& board) {

    // This function handles only the movement of the corresponding
    // rook to the King being castled

    if (piece == nullptr) {
        return;
    }

    int sideI{piece->white ? 7 : 0};

    if (board.grid[sideI][4] == piece) {
        if (sideI == i && j == 6) {
            // King's castle
            board.grid[sideI][5] = board.grid[sideI][7];
            board.grid[sideI][5]->updatePos(sideI, 5);
            board.grid[sideI][7] = nullptr;
        } else if (sideI == i && j == 2) {
            // Queen's castle
            board.grid[sideI][3] = board.grid[sideI][0];
            board.grid[sideI][3]->updatePos(sideI, 3);
            board.grid[sideI][0] = nullptr;                
        }
    }
}

void undoCastle(Board& board) {

    Piece* piece{get<0>(board.moveStack.back())};
    Piece* killed{get<1>(board.moveStack.back())};
    const pair<int,int> initPos{get<2>(board.moveStack.back())};
    const pair<int,int> finPos{get<3>(board.moveStack.back())};

    int sideI{piece->white ? 7 : 0};

    if (initPos.first == sideI && initPos.second == 4) {
        // Condition where the piece moved was king
        if (initPos.first == finPos.first) {
            // Condition where king moved horizontally more than 1 square (castle)
            if (finPos.second - initPos.second > 1) {
                board.grid[sideI][7] = board.grid[sideI][5];
                board.grid[sideI][7]->updatePos(sideI, 7);
                board.grid[sideI][5] = nullptr;
                board.moveStack.pop_back();
            } else if (initPos.second - finPos.second > 1) {
                board.grid[sideI][0] = board.grid[sideI][2];
                board.grid[sideI][0]->updatePos(sideI, 0);
                board.grid[sideI][2] = nullptr;
                board.moveStack.pop_back();
            }
        }
    }

}