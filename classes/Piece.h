#ifndef PIECE
#define PIECE

#include <vector>

using namespace std;

class Piece {
    private:
        virtual void move(const int&i, const int& j) = 0;
        virtual bool is_valid(const int&i, const int& j) const = 0;

    protected:
        Piece(vector<vector<Piece*>>& grid, int i, int j, bool alive, bool white);
        bool is_available(const int& i, const int& j);
        vector<vector<Piece*>> grid;
        int i;
        int j;
        bool alive;
        bool white;
};

#endif