#include "classes/Board.cc"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

void movePiece(Piece* piece, Board& board, const int& i, const int& j, bool test = false);
void printBoard(Board& board);
bool inCheck(Piece* king, Board& board);
vector<pair<int,int>> filterCheckedMoves(Piece* king, Piece* piece, vector<pair<int,int>> validMoves, Board& board);
void castle(Piece* piece, const int& i, const int& j, Board& board);
void undoCastle(Board& board);
void enPassant(Piece* piece, const int& i, const int& j, Board& board);
bool promote(Piece* piece, const int& i, const int& j, Board& board, bool test);

int main() {

    // Create the window
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "My window");

    // Create squares corresponding to checkerboard pattern
    vector<sf::RectangleShape> rectangles;
    for (int i{0}; i < 8; i++) {
        for (int j{0}; j < 8; j++) {
            // Create 200x200 square and set corresponding position
            sf::RectangleShape rect{sf::Vector2f{200, 200}};
            rect.setPosition(i * 200, j * 200);
            rect.setFillColor((i + j) % 2 == 0 ? sf::Color{96, 214, 98, 0} : sf::Color{255, 255, 255, 1});
            rectangles.push_back(rect);
        }
    }


    // sf::RectangleShape rect1(sf::Vector2f(200, 200));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        for (const auto& rect : rectangles) {
            window.draw(rect);
        }



        // end the current frame
        window.display();
    }    

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


void movePiece(Piece* piece, Board& board, const int& i, const int& j, bool test) {

    Piece* newPos{board.grid[i][j]};

    // Update stack of moves (piece being moved, piece being killed, and position updates)
    board.moveStack.push_back({piece, newPos, piece->getPos(), {i, j}});
    if (newPos == nullptr) {
        // Rook moves only if the conditions for castling are satisfied
        castle(piece, i, j, board);
        enPassant(piece, i, j, board);
        promote(piece, i, j, board, test);
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
        if (!promote(piece, i, j, board, test)) {
            piece->updatePos(i, j);
            board.grid[i][j] = piece;
        }
    }

}

void undoMove(Board& board) {

    Piece* piece{get<0>(board.moveStack.back())};
    Piece* killed{get<1>(board.moveStack.back())};
    const pair<int,int> initPos{get<2>(board.moveStack.back())};
    const pair<int,int> finPos{get<3>(board.moveStack.back())};

    undoCastle(board);

    // Internal update of position
    piece->updatePos(initPos.first, initPos.second, true);

    // Update positioning according to grid
    board.grid[initPos.first][initPos.second] = piece;
    board.grid[finPos.first][finPos.second] = nullptr;

    if (killed != nullptr) {
        (piece->white ? board.deadBlack : board.deadWhite).erase(killed);
        board.grid[killed->getPos().first][killed->getPos().second] = killed;
    }

    board.moveStack.pop_back();

}

bool inCheck(Piece* king, Board& board) {

    // Strategy: Get the position of the king,
    // and compare the valid moves of all the other 
    // pieces of the opposite color and see if they
    // coincide. If so, then the king is being Checked.

    pair<int,int> kingPos{king->getPos()};

    if (king->white) {
        for (const auto& blackPiece : board.black) {
            if (board.deadBlack.count(blackPiece) == 0) {
                for (const auto& move : blackPiece->getValidMoves()) {
                    if (move == kingPos) {
                        return true;
                    }
                }
            }
        }
    } else {
        for (const auto& whitePiece : board.white) {
            if (board.deadWhite.count(whitePiece) == 0) {
                for (const auto& move : whitePiece->getValidMoves()) {
                    if (move == kingPos) {
                        return true;
                    }
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
        movePiece(piece, board, move.first, move.second, true);
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

void enPassant(Piece* piece, const int& i, const int& j, Board& board) {

    if (piece->getSHName() != "p") {
        // Assertion that piece is a pawn
        return;
    }

    // Remove the move that just occurred so it can be modified and re-added
    tuple<Piece*,Piece*,pair<int,int>,pair<int,int>> backup{board.moveStack.back()};
    board.moveStack.pop_back();

    if (!board.moveStack.empty()) {
        tuple<Piece*,Piece*,pair<int,int>,pair<int,int>> lastMove{board.moveStack.back()};
        if (get<0>(lastMove)->getSHName() == "p" && get<0>(lastMove)->white != piece->white) {
            // Condition where piece is pawn and pieces are opposite colors
            if (abs(get<2>(lastMove).first - get<3>(lastMove).first) == 2 && abs(get<3>(lastMove).second - piece->getPos().second) == 1) {
                // Condition where pawn moved two steps forward and is beside this pawn
                if (i == (piece->white ? piece->getPos().first - 1 : piece->getPos().second + 1) && j == get<3>(lastMove).second) {
                    // Remove the pawn being attacked by En Passant
                    if (piece->white) {
                        board.deadBlack.insert(get<0>(lastMove));
                    } else {
                        board.deadWhite.insert(get<0>(lastMove));
                    }
                    board.grid[get<3>(lastMove).first][get<3>(lastMove).second] = nullptr;
                    board.moveStack.push_back({piece, get<0>(lastMove), {piece->getPos().first, piece->getPos().second}, {i, j}});
                } else {
                    board.moveStack.push_back(backup);
                }
            } else {
                board.moveStack.push_back(backup);
            }
        } else {
            board.moveStack.push_back(backup);
        }
    } else {
        board.moveStack.push_back(backup);
    }
}

bool promote(Piece* piece, const int& i, const int& j, Board& board, bool test) {

    // Returns false if the grid needs to be updated elsewhere, otherwise
    // return true.

    if (piece->getSHName() == "p") {
        int promoteI{piece->white ? 0 : 7};
        if (i == promoteI) {

            // Remove the move that just occurred so it can be modified and re-added
            tuple<Piece*,Piece*,pair<int,int>,pair<int,int>> backup{board.moveStack.back()};
            board.moveStack.pop_back();

            // This condition will be satisfied when all the possible next moves are being
            // tested. In this case, the promoted piece is not relevant.
            if (test) {
                board.moveStack.push_back(backup);
                return true;
            }

            int promotion;
            do {
                cout << "Choose which piece you would like to promote your Pawn to: " << endl;
                cout << "1) Rook" << endl;
                cout << "2) Knight" << endl;
                cout << "3) Bishop" << endl;
                cout << "4) Queen" << endl;
                cin >> promotion;
            } while (promotion < 1 || promotion > 4);

            Piece* promoted;

            if (promotion == 1) {
                promoted = new Rook{board.grid, board.moveStack, i, j, piece->white};
            } else if (promotion == 2) {
                promoted = new Knight{board.grid, board.moveStack, i, j, piece->white};
            } else if (promotion == 3) {
                promoted = new Bishop{board.grid, board.moveStack, i, j, piece->white};
            } else {
                promoted = new Queen{board.grid, board.moveStack, i, j, piece->white};
            }

            // Kill the pawn being promoted
            (piece->white ? board.deadWhite : board.deadBlack).insert(piece);
            (piece->white ? board.white : board.black).insert(promoted);

            cout << promoted->getSHName() << endl;
            // Set location of promoted
            board.grid[i][j] = promoted;

            // Correct moveStack
            board.moveStack.push_back({promoted, piece, piece->getPos(), {i, j}});

            return true;
        }
    }
    return false;
}