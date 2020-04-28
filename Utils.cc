#include "Utils.h"

bool Utils::promote(Piece* piece, const int& i, const int& j, Board& board, bool test) {

    // Returns false if the grid needs to be updated elsewhere, otherwise
    // return true.

    if (piece->getSHName() == "p") {
        int promoteI{piece->white ? 0 : 7};
        if (i == promoteI) {

            // Remove the move that just occurred so it can be modified and re-added
            std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>> backup{board.moveStack.back()};
            board.moveStack.pop_back();

            // This condition will be satisfied when all the possible next moves are being
            // tested. In this case, the promoted piece is not relevant.
            if (test) {
                board.moveStack.push_back(backup);
                return true;
            }

            int promotion;
            do {
                std::cout << "Choose which piece you would like to promote your Pawn to: " << std::endl;
                std::cout << "1) Rook" << std::endl;
                std::cout << "2) Knight" << std::endl;
                std::cout << "3) Bishop" << std::endl;
                std::cout << "4) Queen" << std::endl;
                std::cin >> promotion;
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

            std::cout << promoted->getSHName() << std::endl;
            // Set location of promoted
            board.grid[i][j] = nullptr;
            board.grid[i][j] = promoted;

            // Correct moveStack
            board.moveStack.push_back({promoted, piece, piece->getPos(), {i, j}});

            return true;
        }
    }
    return false;
}

void Utils::enPassant(Piece* piece, const int& i, const int& j, Board& board) {

    if (piece->getSHName() != "p") {
        // Assertion that piece is a pawn
        return;
    }

    // Remove the move that just occurred so it can be modified and re-added
    std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>> backup{board.moveStack.back()};
    board.moveStack.pop_back();

    if (!board.moveStack.empty()) {
        std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>> lastMove{board.moveStack.back()};
        if (std::get<0>(lastMove)->getSHName() == "p" && std::get<0>(lastMove)->white != piece->white) {
            // Condition where piece is pawn and pieces are opposite colors
            if (std::abs(std::get<2>(lastMove).first - std::get<3>(lastMove).first) == 2 && std::abs(std::get<3>(lastMove).second - piece->getPos().second) == 1) {
                // Condition where pawn moved two steps forward and is beside this pawn
                if (i == (piece->white ? piece->getPos().first - 1 : piece->getPos().second + 1) && j == std::get<3>(lastMove).second) {
                    // Remove the pawn being attacked by En Passant
                    if (piece->white) {
                        board.deadBlack.insert(std::get<0>(lastMove));
                    } else {
                        board.deadWhite.insert(std::get<0>(lastMove));
                    }
                    board.grid[std::get<3>(lastMove).first][std::get<3>(lastMove).second] = nullptr;
                    board.moveStack.push_back({piece, std::get<0>(lastMove), {piece->getPos().first, piece->getPos().second}, {i, j}});
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

void Utils::undoCastle(Board& board) {

    Piece* piece{std::get<0>(board.moveStack.back())};
    Piece* killed{std::get<1>(board.moveStack.back())};
    const std::pair<int,int> initPos{std::get<2>(board.moveStack.back())};
    const std::pair<int,int> finPos{std::get<3>(board.moveStack.back())};

    if (piece->getSHName() != "K") {
        return;
    }

    int sideI{piece->white ? 7 : 0};

    if (initPos.first == sideI && initPos.second == 4) {
        // Condition where the piece moved was king
        if (initPos.first == finPos.first) {
            // Condition where king moved horizontally more than 1 square (castle)
            if (finPos.second - initPos.second > 1) {
                board.grid[sideI][7] = board.grid[sideI][5];
                board.grid[sideI][7]->updatePos(sideI, 7, true);
                board.grid[sideI][5] = nullptr;
                board.moveStack.pop_back();
            } else if (initPos.second - finPos.second > 1) {
                board.grid[sideI][0] = board.grid[sideI][3];
                board.grid[sideI][0]->updatePos(sideI, 0, true);
                board.grid[sideI][3] = nullptr;
                board.moveStack.pop_back();
            }
        }
    }

}

void Utils::castle(Piece* piece, const int& i, const int& j, Board& board) {

    // This function handles only the movement of the corresponding
    // rook to the King being castled

    if (piece == nullptr || piece->getSHName() != "K") {
        return;
    }

    int sideI{piece->white ? 7 : 0};

    if (board.grid[sideI][4] == piece) {
        if (sideI == i && j == 6) {
            // King's castle
            board.grid[sideI][5] = board.grid[sideI][7];
            board.grid[sideI][7] = nullptr;
            board.grid[sideI][5]->updatePos(sideI, 5);
        } else if (sideI == i && j == 2) {
            // Queen's castle
            board.grid[sideI][3] = board.grid[sideI][0];
            board.grid[sideI][0] = nullptr;
            board.grid[sideI][3]->updatePos(sideI, 3);
        }
    }
}

std::vector<std::pair<int,int>> Utils::filterCheckedMoves(Piece* king, Piece* piece, std::vector<std::pair<int,int>> validMoves, Board& board) {

    std::pair<int,int> piecePos{piece->getPos()};
    std::vector<std::pair<int,int>> filteredMoves;

    for (const auto& move : validMoves) {
        movePiece(piece, board, move.first, move.second, true);
        if (!inCheck(king, board)) {
            filteredMoves.push_back(move);
        }
        undoMove(board);
    }
    return filteredMoves;
}


bool Utils::inCheck(Piece* king, Board& board) {

    // Strategy: Get the position of the king,
    // and compare the valid moves of all the other 
    // pieces of the opposite color and see if they
    // coincide. If so, then the king is being Checked.


    std::pair<int,int> kingPos{king->getPos()};

    if (king->white) {
        int i{0};
        for (const auto& blackPiece : board.black) {
            if (board.deadBlack.count(blackPiece) == 0) {
                for (const auto& move : blackPiece->getValidMoves()) {
                    if (move.first == kingPos.first && move.second == kingPos.second) {
                        return true;
                    }
                }
            }
        }
    } else {
        for (const auto& whitePiece : board.white) {
            if (board.deadWhite.count(whitePiece) == 0) {
                for (const auto& move : whitePiece->getValidMoves()) {
                    if (move.first == kingPos.first && move.second == kingPos.second) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


void Utils::printBoard(Board& board) {
    std::cout << "  | 0 1 2 3 4 5 6 7" << std::endl;
    std::cout << "-------------------" << std::endl;
    int i{0};
    for (const auto& row : board.grid) {
        std::cout << i << " | ";
        for (const auto& square : row) {
            if (square == nullptr) {
                std::cout << "  ";
            } else {
                std::cout << square->getSHName();
                if (square->white) {
                    std::cout << "*";
                } else {
                    std::cout << " ";
                }
            }
        }
        i++;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Utils::movePiece(Piece* piece, Board& board, const int& i, const int& j, bool test) {

    Piece* newPos{board.grid[i][j]};

    // Update stack of moves (piece being moved, piece being killed, and position updates)
    board.moveStack.push_back({piece, newPos, piece->getPos(), {i, j}});
    if (newPos == nullptr) {
        // Rook moves only if the conditions for castling are satisfied
        castle(piece, i, j, board);
        enPassant(piece, i, j, board);
        board.grid[piece->getPos().first][piece->getPos().second] = nullptr;
        if (!promote(piece, i, j, board, test)) {
            board.grid[i][j] = piece;
        }
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
            board.grid[i][j] = piece;
            piece->updatePos(i, j);
        }
    }
    if (board.moveStack.size() > 3) {
        board.moveStack.erase(board.moveStack.begin());
    }

}

void Utils::undoMove(Board& board) {

    Piece* piece{std::get<0>(board.moveStack.back())};
    Piece* killed{std::get<1>(board.moveStack.back())};
    const std::pair<int,int> initPos{std::get<2>(board.moveStack.back())};
    const std::pair<int,int> finPos{std::get<3>(board.moveStack.back())};

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

