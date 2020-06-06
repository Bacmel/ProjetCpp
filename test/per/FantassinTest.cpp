#include "per/Fantassin.hpp"
#include <memory>
#include "catch.hpp"
#include "hex/Coordonnees.hpp"
#include "obj/GravityGun.hpp"

using namespace per;

TEST_CASE("Test surcharge de Fantassin", "[Fantassin]")
{
    APersonnage_S fantassin1 = std::make_shared<Fantassin>();
    obj::IObjet_S objet1 = std::make_shared<obj::GravityGun>();
    obj::IObjet_S objet2 = std::make_shared<obj::GravityGun>();

    SECTION("Fantassin::accepter")
    {
        // A tester.
    }

    SECTION("Fantassin::ajouterObjet")
    {
        REQUIRE(fantassin1->tailleSac() == 1);
        REQUIRE_THROWS(fantassin1->ajouterObjet(objet1));
        REQUIRE(fantassin1->tailleSac() == 1);
    }

    SECTION("Fantassin::retirerObjet")
    {
        REQUIRE(fantassin1->tailleSac() == 1);
        REQUIRE_THROWS(fantassin1->retirerObjet(fantassin1->getObjet(0)));
        REQUIRE(fantassin1->tailleSac() == 1);
    }

    SECTION("Fantassin::tailleSac") { REQUIRE(fantassin1->tailleSac() == 1); }

    SECTION("Fantassin::actualiser")
    {
        // A tester.
    }

    SECTION("Fantassin::getPorte") { REQUIRE(fantassin1->getPorte() == hex::Masque::contour()); }

    SECTION("Fantassin::getZoneDegat")
    {
        hex::Coordonnees c1 = hex::Coordonnees::direction(hex::Direction::Nord);
        hex::Masque m1;
        REQUIRE(fantassin1->getZoneDegat(c1) == m1);
    }
}