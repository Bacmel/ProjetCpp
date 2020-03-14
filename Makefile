CXX = g++
CXXFLAGS = -Iinclude

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = jeu

build: $(OBJ)
	g++ -o $(BIN) $^ $(LIBS)

.PHONY: clear
clear:
	rm -rf src/*.o

vclear: clear
	rm -rf $(BIN)
