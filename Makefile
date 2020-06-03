CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -g -O0

LDFLAGS = # Paramètres : -L
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

HDR = $(wildcard include/*.hpp) $(wildcard include/*/*.hpp) # Liste des fichiers d'entêtes
SRC = $(wildcard src/*/*.cpp) $(wildcard src/*/*/*.cpp) # Liste des fichiers sources
OBJ = $(SRC:.cpp=.o) # Liste des fichiers objets
BIN = Jeu # Nom de l'exécutable

SRCT = $(wildcard test/*.cpp) $(wildcard test/*/*.cpp)
OBJT = $(SRCT:.cpp=.o) $(OBJ)
BINT = Test # Nom de l'exécutable

all: build test

test: $(OBJT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BINT) $^ $(LDLIBS)

build: src/main.o $(OBJ)
	$(CXX) $(LDFLAGS) -o $(BIN) $^ $(LDLIBS)

%.o: $(HDR)

.PHONY: clear
clear:
	rm -f src/main.o test/Test.o $(OBJ) $(OBJT)

.PHONY: vclear
vclear: clear
	rm -f $(BIN) $(BINT)

rebuild: vclear build

retest: vclear test
