#ifndef PIECE
#define PIECE

#include <vector>
#include <string>

using namespace std;

class Piece {
    public:
        virtual ~Piece();
        bool white;
        bool alive;
        virtual vector<pair<int,int>> getValidMoves() const = 0;
        void updatePos(const int& i, const int& j, bool undo = false);
        pair<int,int> getPos() const;
        int getNumMoves() const;
        virtual string getName() const = 0;
        virtual string getSHName() const = 0;
    private:
        virtual void move(const int&i, const int& j) = 0;
        virtual bool isValid(const int&i, const int& j) const = 0;
    protected:
        Piece(vector<vector<Piece*>>& grid, vector<tuple<Piece*,Piece*,pair<int,int>,pair<int,int>>>& moveStack, int i, int j, bool white);
        bool isAvailable(const int& i, const int& j) const;
        vector<vector<Piece*>>& grid;
        vector<tuple<Piece*,Piece*,pair<int,int>,pair<int,int>>>& moveStack;
        bool inRange(const int& i, const int& j) const;
        int i;
        int j;
        int numMoves;
        string name;
};

typedef vector<tuple<Piece*,Piece*,pair<int,int>,pair<int,int>>> MoveStack;

#endif