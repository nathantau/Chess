CXX=g++
CXXFLAGS=-std=c++14

chess: main.o Utils.o Board.o Bishop.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o SpritesManager.o
	$(CXX) $(CXXFLAGS) -o chess main.o Utils.o Board.o Bishop.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o SpritesManager.o -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o