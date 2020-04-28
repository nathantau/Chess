#include "SpritesManager.h"

SpritesManager::SpritesManager() {}

SpritesManager::~SpritesManager() {}

std::string SpritesManager::getFilename(Piece* piece) const {
    return (piece->white ? "W" : "B") + piece->getName() + ".png";
}
