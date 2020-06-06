#include "donjon/cases/Trou.hpp"
#include <memory>
#include "catch.hpp"
#include "obj/GravityGun.hpp"
#include "per/Heros.hpp"

using namespace donjon::cases;
using namespace obj;
using namespace per;

TEST_CASE("Creation et manipulation de Trou", "[Trou]")
{
    Trou trou;

    REQUIRE_FALSE(trou.estPraticable());
    REQUIRE(trou.estTransparent());

    SECTION("Trou::enActivation")
    {
        Heros heros(3);
        // Sauvegarde de l'état du héros.
        size_t sante = heros.getSante();
        size_t santeMax = heros.getSanteMax();
        hex::Coordonnees pos = heros.getPosition();
        bool vie = heros.estVivant();

        trou.enActivation(heros);
        // Pas d'influence sur le héros.
        REQUIRE(heros.getSante() == sante);
        REQUIRE(heros.getSanteMax() == santeMax);
        REQUIRE(heros.getPosition() == pos);
        REQUIRE(heros.estVivant() == vie);
    }

    SECTION("Trou::enEntree")
    {
        Heros heros(3);
        // Sauvegarde de l'état du héros.
        size_t sante = heros.getSante();
        size_t santeMax = heros.getSanteMax();
        hex::Coordonnees pos = heros.getPosition();

        trou.enEntree(heros);
        // Tue le héros.
        REQUIRE_FALSE(heros.getSante() == sante);
        REQUIRE(heros.getSanteMax() == santeMax);
        REQUIRE(heros.getPosition() == pos);
        REQUIRE_FALSE(heros.estVivant());
    }

    SECTION("Trou::deposer")
    {
        IObjet_S objet = std::make_shared<GravityGun>();
        // Dépot d'un objet null.
        REQUIRE_THROWS(trou.deposer(IObjet_S()));
        // Dépot d'un objet sur une case vide.
        REQUIRE_THROWS(trou.deposer(objet));
    }

    SECTION("Trou::ramaser")
    {
        // Ramasser sur un trou.
        REQUIRE_THROWS(trou.ramasser());
    }

    SECTION("Trou::accepter")
    {
        // A Tester.
    }

    SECTION("Trou::actualiser")
    {
        // A Tester.
    }
}
