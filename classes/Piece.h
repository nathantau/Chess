#ifndef PIECE
#define PIECE

#include <vector>

using namespace std;

class Piece {
    public:
        virtual ~Piece();
    private:
        virtual void move(const int&i, const int& j) = 0;
        virtual bool isValid(const int&i, const int& j) const = 0;
    protected:
        Piece(vector<vector<Piece*>>& grid, vector<pair<Piece*,pair<pair<int,int>,pair<int,int>>>>& moveStack, int i, int j, bool white);
        bool isAvailable(const int& i, const int& j) const;
        vector<vector<Piece*>> grid;
        vector<pair<Piece*,pair<pair<int,int>,pair<int,int>>>> moveStack;
        int i;
        int j;
        bool alive;
        bool white;
};

typedef vector<pair<Piece*,pair<pair<int,int>,pair<int,int>>>> MoveStack;

#endif