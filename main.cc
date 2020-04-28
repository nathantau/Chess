#include "Board.h"
#include "SpritesManager.h"
#include "Utils.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>

int main() {

    // Utils
    SpritesManager spritesManager{};
    Board board{};

    // This cache is responsible for saving the textures that have
    // already been loaded in.
    std::unordered_map<Piece*, sf::Texture> textureCache{};

    bool whiteTurn{true};
    bool gameOver{false};
    bool checked{false};
    bool windowLoaded{false};
    bool pieceSelected{false};
    bool pressing{false};

    Piece* whiteKing{board.grid[7][4]};
    Piece* blackKing{board.grid[0][4]};
    Piece* piece{nullptr};

    int i{-1};
    int j{-1};

    // Create the window
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "R&M Chess (pls dont copyright strike)");

    // Create squares corresponding to checkerboard pattern
    std::vector<sf::RectangleShape> rectangles;
    for (int i{0}; i < 8; i++) {
        for (int j{0}; j < 8; j++) {
            // Create 200x200 square and set corresponding position/color
            sf::RectangleShape rect{sf::Vector2f{200, 200}};
            rect.setPosition(i * 200, j * 200);
            rect.setFillColor((i + j) % 2 == 0 ? sf::Color{96, 214, 98, 255} : sf::Color{255, 255, 255, 255});
            rectangles.push_back(rect);
        }
    }
    sf::RectangleShape clickedRect{sf::Vector2f{200, 200}};
    sf::RectangleShape checkRect{sf::Vector2f{200, 200}};
    sf::RectangleShape winRect{sf::Vector2f{200, 200}};
    std::vector<std::pair<int,int>> validMoves;
    std::vector<sf::RectangleShape> validMovesRects;

    // run the program as long as the window is open
    while (window.isOpen()) {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)  {
                window.close();
            }
        }

        // if (gameOver) {
        //     window.close();
        // }

        // Game logic occurs after the window has first loaded
        if (windowLoaded && !gameOver) {
            if (checked) {
                // Condition where player is in check. A full search over the alive
                // pieces of the player's color will determine if any valid moves
                // (filtered) exist. If not, CHECKMATE!
                int numValidMoves{0};
                if (whiteTurn) {
                    for (const auto& whitePiece : board.white) {
                        if (board.deadWhite.count(whitePiece) == 0) {
                            // Condiiton where white piece is alive
                            numValidMoves += Utils::filterCheckedMoves(whiteKing, whitePiece, whitePiece->getValidMoves(), board).size();
                        }
                    }
                    if (numValidMoves == 0) {
                        std::cout << "Black wins!!!" << std::endl;
                        gameOver = true;
                        winRect.setPosition(200 * blackKing->getPos().second, 200 * blackKing->getPos().first);
                    }
                } else {
                    for (const auto& blackPiece : board.black) {
                        if (board.deadBlack.count(blackPiece) == 0) {
                            // Condiiton where white piece is alive
                            numValidMoves += Utils::filterCheckedMoves(blackKing, blackPiece, blackPiece->getValidMoves(), board).size();
                        }
                    }
                    if (numValidMoves == 0) {
                        std::cout << "White wins!!!" << std::endl;
                        gameOver = true;
                        winRect.setPosition(200 * whiteKing->getPos().second, 200 * whiteKing->getPos().first);
                    }
                }
            }

            if (pieceSelected) {

                if (pressing == true) {
                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        // Do nothing...
                    }
                    pressing = false;
                } else {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        sf::Vector2i localPos{sf::Mouse::getPosition(window)};
                        i = localPos.y / 200;
                        j = localPos.x / 200;
                        
                        std::cout << "HELLO" << std::endl;

                        if ((0 <= i && i <= 8 && 0 <= j && j <= 8)) {
                            bool selectedValid{false};
                            for (const auto& move : validMoves) {
                                if (move.first == i && move.second == j) {
                                    // Condition where valid move is selected
                                    selectedValid = true;
                                }
                            }
                            if (selectedValid) {
                                // Condition where piece moves (the turn must switch to avoid hazards)
                                Utils::printBoard(board);
                                Utils::movePiece(piece, board, i, j);
                                Utils::printBoard(board);
                                if (Utils::inCheck(whiteTurn ? blackKing : whiteKing, board)) {
                                    checked = true;
                                } else {
                                    checked = false;
                                }
                                // Switch turns
                                whiteTurn = !whiteTurn;
                                // Reset values for rendering
                                pieceSelected = false;
                                validMoves.clear();
                                validMovesRects.clear();
                            } else {
                                pieceSelected = false;
                                validMoves.clear();
                                validMovesRects.clear();
                                piece = board.grid[i][j];
                                if (!(piece == nullptr || piece->white != whiteTurn || (validMoves = Utils::filterCheckedMoves(piece->white ? whiteKing : blackKing, piece, piece->getValidMoves(), board)).size() == 0)) {
                                    pieceSelected = true;
                                    for (const auto& move : validMoves) {
                                        sf::RectangleShape rect{sf::Vector2f{200, 200}};
                                        rect.setPosition(move.second * 200, move.first * 200);
                                        rect.setFillColor((move.first + move.second) % 2 == 0 ? sf::Color{224, 215, 108, 255} : sf::Color{237, 227, 114, 255});
                                        validMovesRects.push_back(rect);
                                    }
                                }                            
                            }
                        }
                    }
                }
            } else {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i localPos{sf::Mouse::getPosition(window)};
                    i = localPos.y / 200;
                    j = localPos.x / 200;
                    std::cout << i << " " << j << std::endl;
                    piece = board.grid[i][j];
                    Utils::printBoard(board);
                    if (piece != nullptr && piece->white == whiteTurn && (validMoves = Utils::filterCheckedMoves(piece->white ? whiteKing : blackKing, piece, piece->getValidMoves(), board)).size() != 0) {
                        // std::cout << "HELLO FUCKER" << std::endl;
                        pieceSelected = true;
                        pressing = true;
                        for (const auto& move : validMoves) {
                            // std::cout << move.first << " " << move.second << std::endl;
                            sf::RectangleShape rect{sf::Vector2f{200, 200}};
                            rect.setPosition(move.second * 200, move.first * 200);
                            rect.setFillColor((move.first + move.second) % 2 == 0 ? sf::Color{224, 215, 108, 255} : sf::Color{237, 227, 114, 255});
                            validMovesRects.push_back(rect);
                        }
                    }        
                }
            }



        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // Draw background checkerboard
        for (const auto& rect : rectangles) {
            window.draw(rect);
        }        
        // Draw valid moves
        for (const auto& rect : validMovesRects) {
            window.draw(rect);
        }

        if (0 <= i && i <= 8 && 0 <= j && j <= 8) {
            clickedRect.setPosition(j * 200, i * 200);
            clickedRect.setFillColor((i + j) % 2 == 0 ? sf::Color{224, 215, 108, 255} : sf::Color{237, 227, 114, 255});
            window.draw(clickedRect);
        }

        if (checked) {
            checkRect.setPosition(200 * (whiteTurn ? whiteKing->getPos().second : blackKing->getPos().second), 200 * (whiteTurn ? whiteKing->getPos().first : blackKing->getPos().first));
            checkRect.setFillColor(sf::Color{214, 112, 84, 255});
            window.draw(checkRect);
        }

        if (gameOver) {
            winRect.setFillColor(sf::Color{111, 204, 237, 255});
            window.draw(winRect);
        }

        // Load and draw sprites (if they are alive)
        for (const auto& piece : board.white) {
            if (board.deadWhite.count(piece) == 0) {
                if (textureCache.count(piece) == 1) {
                    // Condition where cache saved piece's sprite
                    sf::Sprite sprite{textureCache[piece]};                    
                    sprite.setPosition(piece->getPos().second * 200, piece->getPos().first * 200);
                    window.draw(sprite);
                } else {
                    sf::Texture texture;
                    texture.loadFromFile("sprites/" + spritesManager.getFilename(piece));
                    sf::Sprite sprite{texture};
                    textureCache[piece] = texture;
                    sprite.setPosition(piece->getPos().second * 200, piece->getPos().first * 200);
                    window.draw(sprite);
                }
            }
        }

        // Load and draw sprites (if they are alive)
        for (const auto& piece : board.black) {
            if (board.deadBlack.count(piece) == 0) {
                if (textureCache.count(piece) == 1) {
                    // Condition where cache saved piece's sprite
                    sf::Sprite sprite{textureCache[piece]};                    
                    sprite.setPosition(piece->getPos().second * 200, piece->getPos().first * 200);
                    window.draw(sprite);
                } else {
                    sf::Texture texture;
                    texture.loadFromFile("sprites/" + spritesManager.getFilename(piece));
                    sf::Sprite sprite{texture};
                    textureCache[piece] = texture;
                    sprite.setPosition(piece->getPos().second * 200, piece->getPos().first * 200);
                    window.draw(sprite);
                }
            }
        }

        // end the current frame
        window.display();
        windowLoaded = true;
    }    

}

