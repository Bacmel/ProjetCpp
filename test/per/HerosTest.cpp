#include "per/Heros.hpp"
#include "hex/Coordonnees.hpp"
#include "catch.hpp"

using namespace per;

TEST_CASE("Creation et manipulation de heros", "[heros]")
{
    Heros h1(3);
    REQUIRE(h1.getSante() == 3);
    REQUIRE(h1.getSanteMax() == 3);
    REQUIRE(h1.getPosition() == hex::Coordonnees());

    Heros h2(1);
    REQUIRE(h2.getSante() == 1);
    REQUIRE(h2.getSanteMax() == 1);
    REQUIRE(h2.getPosition() == hex::Coordonnees());

    SECTION("APersonnage::estVivant")
    {
        REQUIRE(h1.estVivant());
        REQUIRE(h2.estVivant());
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
        REQUIRE(h2.getSante() == 1);
    }

    SECTION("APersonnage::ajouterSanteMax")
    {
        REQUIRE(h1.estVivant());
        h1.ajouterSanteMax(-3);
        REQUIRE_FALSE(h1.estVivant());
        REQUIRE(h2.estVivant());
        h2.ajouterSanteMax(-3);
        REQUIRE_FALSE(h2.estVivant());
 
        h1.ajouterSanteMax(10);
        REQUIRE(h1.estVivant());
        h1.ajouterSante(999);
        REQUIRE(h1.getSante() == 10);
    }

    SECTION("APersonnage::tuer")
    {
        h1.tuer();
        REQUIRE_FALSE(h1.estVivant());
        h2.tuer();
        REQUIRE_FALSE(h2.estVivant());
    }

    SECTION("deplacer")
    {
        hex::Coordonnees c1(12,46);
        hex::Coordonnees c2(1,0);
        hex::Coordonnees c3(0,2);
        h1.deplacer(per::Deplacement::Forcer, c1);
        REQUIRE(h1.getPosition()==c1);
        h1.deplacer(per::Deplacement::Forcer, hex::Coordonnees());
        REQUIRE_THROWS(h1.deplacer(per::Deplacement::Marcher, c1));
        h1.deplacer(per::Deplacement::Marcher, c2);
        REQUIRE(h1.getPosition()==c2);
        REQUIRE_THROWS(h2.deplacer(per::Deplacement::Sauter, c1));
        h2.deplacer(per::Deplacement::Sauter, c3);
        REQUIRE(h2.getPosition()==c3);
    }
    // TODO ajouter des tests pour les objets
}
