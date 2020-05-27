#include "donjon/Donjon.hpp"
#include <iostream>
#include "catch.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "hex/CarteHexagone.hpp"
#include "per/Heros.hpp"
#include <vector>

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace per;
using namespace std;

TEST_CASE("Creation et manipulation de Donjon", "[Donjon]")
{
    std::cout << "Début du test" << std::endl;
    ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(2));
    function<ICase_S()> fournisseurSol = []() {
        return make_shared<Sol>();
    };
    carte->remplir(fournisseurSol);
    Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
    (*carte)(positionTrou) = ICase_S(new Trou());
    Donjon donjon(carte);

    SECTION("Donjon::invoquer")
    {
        // Invocation sur une case valide.
        APersonnage_S heros(new Heros(3));
        REQUIRE_NOTHROW(donjon.invoquer(heros, Coordonnees()));
        // Invocation sur une case occupée.
        APersonnage_S herosBis(new Heros(2));
        REQUIRE_THROWS(donjon.invoquer(herosBis, Coordonnees()));
        // Invocation sur une case invalide.
        REQUIRE_THROWS(donjon.invoquer(herosBis, positionTrou));
    }
}
