CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -g -O0

LDFLAGS = # Paramètres : -L
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

HDR = $(wildcard include/*.hpp) $(wildcard include/*/*.hpp) # Liste des fichiers d'entêtes
SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp) # Liste des fichiers sources
OBJ = $(SRC:.cpp=.o) # Liste des fichiers objets
BIN = jeu # Nom de l'exécutable

SRCT = $(wildcard test/*/*.cpp) 
OBJT = $(SRCT:.cpp=.o) # Liste des fichiers objets
TEST = test

all: build Test

Test: $(OBJT)
	$(CXX) $(LDFLAGS) -o $@ $^ 

build: $(OBJ)
	$(CXX) $(LDFLAGS) -o $(BIN) $^ $(LDLIBS)

%.o: $(HDR)

.PHONY: clear
clear:
	rm -rf $(OBJ)

.PHONY: vclear
vclear: clear
	rm -rf $(BIN)

rebuild: vclear build
