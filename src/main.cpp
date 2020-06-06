#include "Roblite.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));
    // Création de la classe de plus haut niveau et lancement du jeu.
    Roblite roblite;
    roblite.jouer();
    return 0;
}
