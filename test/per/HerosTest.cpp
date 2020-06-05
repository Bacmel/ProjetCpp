#include "per/Heros.hpp"
#include <memory>
#include "catch.hpp"
#include "hex/Coordonnees.hpp"
#include "obj/GravityGun.hpp"

using namespace per;

TEST_CASE("Creation et manipulation de APersonnage", "[APersonnage]")
{
    APersonnage_S heros1 = std::make_shared<Heros>(3);
    APersonnage_S heros2 = std::make_shared<Heros>(0);

    SECTION("APersonnage::estVivant")
    {
        REQUIRE(heros1->estVivant());
        REQUIRE_FALSE(heros2->estVivant());
    }

    SECTION("APersonnage::subirAttaque")
    {
        REQUIRE(heros1->getSante()==3);
        REQUIRE(heros2->getSante()==0);
        heros1->subirAttaque(2);
        heros2->subirAttaque(2);
        REQUIRE(heros1->getSante()==1);
        REQUIRE(heros2->getSante()==0);
    }

    SECTION("APersonnage::ajouterSante")
    {
        heros1->ajouterSante(-2);
        heros2->ajouterSante(3);
        REQUIRE(heros1->getSante()==1);
        REQUIRE(heros2->getSante()==0);
    }

    SECTION("APersonnage::ajouterSanteMax")
    {
        heros1->ajouterSanteMax(-4);
        heros2->ajouterSanteMax(3);
        REQUIRE(heros1->getSante()==0);
        REQUIRE(heros2->getSante()==3);
        REQUIRE(heros1->getSanteMax()==0);
        REQUIRE(heros2->getSanteMax()==3);
    }

    SECTION("APersonnage::tuer")
    {
        heros1->tuer();
        REQUIRE(heros1->getSante()==0);
        REQUIRE_FALSE(heros1->estVivant());
    }

    SECTION("APersonnage::deplacer")
    {
        hex::Coordonnees marche(1,0);
        hex::Coordonnees saut(2,0);
        hex::Coordonnees force(5,-15);
        /* Test saut. */
        REQUIRE_THROWS(heros1->deplacer(Deplacement::Sauter,marche));
        REQUIRE_THROWS(heros1->deplacer(Deplacement::Sauter,force));
        REQUIRE_NOTHROW(heros1->deplacer(Deplacement::Sauter, saut));
        REQUIRE(heros1->getPosition()==saut);
        /* Test saut. */
        REQUIRE_THROWS(heros1->deplacer(Deplacement::Marcher,saut));
        REQUIRE_THROWS(heros1->deplacer(Deplacement::Marcher,force));
        REQUIRE_NOTHROW(heros1->deplacer(Deplacement::Marcher, marche));
        REQUIRE(heros1->getPosition()==marche);
        /* Test force. */
        REQUIRE_NOTHROW(heros1->deplacer(Deplacement::Forcer, marche));
        REQUIRE_NOTHROW(heros1->deplacer(Deplacement::Forcer, saut));
        REQUIRE_NOTHROW(heros1->deplacer(Deplacement::Forcer, force));
    }
}

TEST_CASE("Manipulation inventaire du Heros","[Heros]")
{
    APersonnage_S heros1 = std::make_shared<Heros>(3);
    obj::IObjet_S objet1 = std::make_shared<obj::GravityGun>();
    obj::IObjet_S objet2 = std::make_shared<obj::GravityGun>();

    SECTION("Heros::ajouterObjet")
    {
        REQUIRE(heros1->tailleSac()==0);
        REQUIRE_NOTHROW(heros1->ajouterObjet(objet1));
        REQUIRE(heros1->tailleSac()==1);
        REQUIRE(heros1->getObjet(0)==objet1);
    }

    SECTION("Heros::retirerObjet")
    {
        REQUIRE(heros1->tailleSac()==0);
        REQUIRE_NOTHROW(heros1->ajouterObjet(objet1));
        REQUIRE(heros1->tailleSac()==1);
        REQUIRE_NOTHROW(heros1->retirerObjet(objet1));
        REQUIRE(heros1->tailleSac()==0);
    }
}