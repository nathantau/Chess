#ifndef PIECE
#define PIECE

#include <vector>
#include <string>

class Piece {
    public:
        virtual ~Piece();
        bool white;
        bool alive;
        virtual std::vector<std::pair<int,int>> getValidMoves() const = 0;
        void updatePos(const int& i, const int& j, bool undo = false);
        std::pair<int,int> getPos() const;
        int getNumMoves() const;
        int setNumMoves(const int& numMoves);
        virtual std::string getName() const = 0;
        virtual std::string getSHName() const = 0;
    private:
    protected:
        Piece(std::vector<std::vector<Piece*>>& grid, std::vector<std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>>>& moveStack, int i, int j, bool white);
        bool isAvailable(const int& i, const int& j) const;
        std::vector<std::vector<Piece*>>& grid;
        std::vector<std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>>>& moveStack;
        bool inRange(const int& i, const int& j) const;
        int i;
        int j;
        int numMoves;
        std::string name;
};

typedef std::vector<std::tuple<Piece*,Piece*,std::pair<int,int>,std::pair<int,int>>> MoveStack;

#endif