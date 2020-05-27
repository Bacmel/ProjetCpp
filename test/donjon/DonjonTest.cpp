#include "donjon/Donjon.hpp"
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "donjon/cases/Sol.hpp"
#include "donjon/cases/Trou.hpp"
#include "hex/CarteHexagone.hpp"
#include "per/Heros.hpp"

using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace per;
using namespace std;

TEST_CASE("Creation et manipulation de Donjon", "[Donjon]")
{
    ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(2));
    function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
    carte->remplir(fournisseurSol);
    Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
    (*carte)(positionTrou) = ICase_S(new Trou());
    Donjon donjon(carte);

    SECTION("Donjon::invoquer")
    {
        // Invocation sur une case valide.
        APersonnage_S heros(new Heros(3));
        Coordonnees pos(-1, 2);
        REQUIRE_NOTHROW(donjon.invoquer(heros, pos));
        REQUIRE(heros->getPosition() == pos);
        // Invocation sur une case occupée.
        APersonnage_S herosBis(new Heros(2));
        REQUIRE_THROWS(donjon.invoquer(herosBis, pos));
        // Invocation sur une case invalide.
        REQUIRE_THROWS(donjon.invoquer(herosBis, positionTrou));
        // Invocation d'un personnage déjà présent.
        REQUIRE_THROWS(donjon.invoquer(heros, Coordonnees().translate(Direction::Sud)));
    }

    SECTION("Donjon::deplacer")
    {
        // Invocation sur une case valide.
        APersonnage_S heros(new Heros(3));
        Coordonnees pos(0, 0);
        donjon.invoquer(heros, pos);
        // Déplacement vers une case interdite.
        REQUIRE_THROWS(donjon.deplace(*heros, Deplacement::Forcer, pos.translate(Direction::Nord)));
        // Déplacement hors carte.
        REQUIRE_THROWS(donjon.deplace(*heros, Deplacement::Forcer, pos.translate(Direction::NordEst, 4)));
        // Déplacement vers une case occupée.
        APersonnage_S herosBis(new Heros(1));
        Coordonnees posBis = pos.translate(Direction::Sud);
        donjon.invoquer(herosBis, posBis);
        REQUIRE_THROWS(donjon.deplace(*heros, Deplacement::Forcer, posBis));
        // Déplacement valide
        Coordonnees destination = pos.translate(Direction::NordEst);
        REQUIRE_NOTHROW(donjon.deplace(*heros, Deplacement::Forcer, destination));
        REQUIRE(heros->getPosition() == destination);
    }
}
