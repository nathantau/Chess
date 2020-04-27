#ifndef SPRITESMANAGER
#define SPRITESMANAGER

#include <unordered_map>
#include "Piece.h"

class SpritesManager {
    public:
        SpritesManager();
        virtual ~SpritesManager();
        std::string getFilename(Piece* piece) const;        
};

#endif