CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -g -O0

LDFLAGS = # Paramètres : -L
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

HDR = $(wildcard include/*.hpp) $(wildcard include/hex/*.hpp) $(wildcard include/obj/*.hpp) # Liste des fichiers d'entêtes
SRC = $(wildcard src/*.cpp) $(wildcard src/hex/*.cpp) $(wildcard include/obj/*.cpp) # Liste des fichiers sources
OBJ = $(SRC:.cpp=.o) # Liste des fichiers objets
BIN = jeu # Nom de l'exécutable

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
