#include "per/Heros.hpp"
#include "hex/Coordonnees.hpp"
#include "catch.hpp"

using namespace per;

TEST_CASE("Creation et manipulation de heros", "[heros]")
{
    Heros h1(3);
    REQUIRE(h1.getSante() == 3);
    REQUIRE(h1.getSanteMax() == 3);
    REQUIRE(h1.getId() == 0);
    REQUIRE(h1.getPosition() == hex::Coordonnees());

    Heros h2(1);
    REQUIRE(h2.getSante() == 1);
    REQUIRE(h2.getSanteMax() == 1);
    REQUIRE(h2.getId() == 1);
    REQUIRE(h2.getPosition() == hex::Coordonnees());

    SECTION("APersonnage::estVivant")
    {
        REQUIRE(h1.estVivant());
        REQUIRE_FALSE(h2.estVivant());
    }

    SECTION("APersonnage::subitAttaque")
    {
        h1.subitAttaque(1);
        REQUIRE(h1.estVivant());
        h1.subitAttaque(2);
        REQUIRE_FALSE(h1.estVivant());
        h2.subitAttaque(999);
        REQUIRE_FALSE(h2.estVivant());
    }

    SECTION("APersonnage::ajouterSante")
    {
        // Tue le héros par sa santé.
        REQUIRE(h1.estVivant());
        h1.ajouterSante(-3);
        REQUIRE_FALSE(h1.estVivant());
        REQUIRE(h2.estVivant());
        h2.ajouterSante(-3);
        REQUIRE_FALSE(h2.estVivant());
 
        h1.ajouterSante(3);
        h2.ajouterSante(999);
        REQUIRE(h1.estVivant());
        REQUIRE(h2.getSante() == 3);
    }

    SECTION("APersonnage::ajouterSanteMax")
    {
        // Tue le héros par sa santé.
        REQUIRE(h1.estVivant());
        h1.ajouterSante(-3);
        REQUIRE_FALSE(h1.estVivant());
        REQUIRE(h2.estVivant());
        h2.ajouterSante(-3);
        REQUIRE_FALSE(h2.estVivant());
 
        h1.ajouterSante(-3);
        REQUIRE_FALSE(h1.estVivant());
        REQUIRE(h2.estVivant());
        h2.ajouterSante(-3);
        REQUIRE_FALSE(h2.estVivant());
    }

    SECTION("APersonnage::tuer")
    {
        h1.tuer();
        REQUIRE_FALSE(h1.estVivant());
        h2.tuer();
        REQUIRE_FALSE(h2.estVivant());
    }
    // TODO ajouter des tests pour les objets
}
